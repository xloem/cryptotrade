#include "OrderbookCompressedHistory.hpp"

OrderbookCompressedHistory::Iterator & OrderbookCompressedHistory::Iterator::operator++()
{
	Delta * delta = nullptr;
	if (obook == nullptr)
	{
		return *this;
	}
	while (true)
	{
		if (deltaIdx >= obook->deltas.GetEntriesFast())
		{
			obook = nullptr;
			return *this;
		}
		delta = (Delta*)obook->deltas.At(deltaIdx);
		if (entryIdx == 0)
		{
			std::get<0>(timeQuoteDepth) += delta->timestamp;
		}
		if (entryIdx >= delta->depths.GetSize())
		{
			entryIdx = 0;
			++ deltaIdx;
			continue;
		}
		break;
	}
	if (entryIdx == 0)
	{
		std::get<1>(timeQuoteDepth) = delta->baseQuote;
	}
	else
	{
		std::get<1>(timeQuoteDepth) += delta->quotes.At(entryIdx - 1);
	}
	// expressions combined to quickly ensure only 1 map lookup
	std::get<2>(timeQuoteDepth) = (depths[std::get<1>(timeQuoteDepth)] += delta->depths.At(entryIdx));
	++ entryIdx;
	return *this;
};

std::tuple<Long64_t, Long64_t, Long64_t> const & OrderbookCompressedHistory::Iterator::operator*() const
{
	return timeQuoteDepth;
}

bool OrderbookCompressedHistory::Iterator::operator!=(Iterator const & other)
{
	if (other.obook == nullptr || obook != other.obook)
	{
		return obook != other.obook;
	}
	return deltaIdx != other.deltaIdx  || entryIdx != other.entryIdx;
}

OrderbookCompressedHistory::Iterator::Iterator(OrderbookCompressedHistory *obook)
: obook(obook),
  deltaIdx(0),
  entryIdx(0)
{
	if (obook != nullptr)
	{
		std::get<0>(timeQuoteDepth) = obook->baseTimestamp;
		++(*this);
	}
}

OrderbookCompressedHistoryFactory::OrderbookCompressedHistoryFactory(OrderbookCompressedHistory & chunk)
: chunk(chunk),
  lastTimestamp(chunk.baseTimestamp)
{
	for (auto const & entry : chunk)
	{
		lastTimestamp = std::get<0>(entry);
		lastQuote = std::get<1>(entry);
		auto depth = std::get<2>(entry);
		runningDepths[lastQuote] = depth;
	}
}

void OrderbookCompressedHistoryFactory::advance(Long64_t timestamp)
{
	if (chunk.deltas.GetEntriesFast() == 0)
	{
		// first one
		chunk.baseTimestamp = timestamp;
		lastTimestamp = timestamp;
	}
	else
	{
		if (timestamp == lastTimestamp)
		{
			return;
		}
		finishEntry();
	}

	while (timestamp - lastTimestamp > 255)
	{
		Delta * delta = new Delta();
		delta->timestamp = 255;
		delta->baseQuote = 0;
		chunk.deltas.Add(delta);
		lastTimestamp += 255;
	}
	
	Delta * delta = new Delta();
	delta->timestamp = timestamp - lastTimestamp;
	delta->quotes.Set(256);
	delta->depths.Set(256);
	numDeltaEntries = 0;
	chunk.deltas.Add(delta);
}

void OrderbookCompressedHistoryFactory::finishEntry()
{
	Delta * delta = (Delta *)chunk.deltas.Last();
	delta->quotes.Set(numDeltaEntries > 1 ? numDeltaEntries - 1 : 0);
	delta->depths.Set(numDeltaEntries);
}

void OrderbookCompressedHistoryFactory::addEntry(Long64_t quote, Long64_t depth)
{
	if (runningDepths[quote] == depth)
	{
		return;
	}

	Delta * delta = (Delta *)chunk.deltas.Last();
	if (numDeltaEntries == 0)
	{
		delta->baseQuote = quote;
		lastQuote = quote;
	}
	else
	{
		while (lastQuote < quote - 0x7fffffff)
		{
			addDeltaEntry(0x7fffffff, 0);
		}
		auto lastDepth = runningDepths[quote];
		Int_t deltaQuote = quote - lastQuote;
		if (depth > lastDepth)
		{
			while (depth - lastDepth > 0x7fffffff)
			{
				addDeltaEntry(deltaQuote, 0x7fffffff);
				lastDepth = runningDepths[quote];
				deltaQuote = 0;
			}
		}
		else
		{
			while (lastDepth - depth > 0x80000000)
			{
				addDeltaEntry(deltaQuote, -0x80000000);
				lastDepth = runningDepths[quote];
				deltaQuote = 0;
			}
		}
		addDeltaEntry(deltaQuote, depth - lastDepth);
	}
}

void OrderbookCompressedHistoryFactory::addChunk(OrderbookCompressedHistory & chunk)
{
	for (auto const & entry : chunk)
	{
		auto timestamp = std::get<0>(entry);
		auto quote = std::get<1>(entry);
		auto depth = std::get<2>(entry);
		if (timestamp != lastTimestamp) {
			advance(timestamp);
		}
		addEntry(quote, depth);
	}
}

void OrderbookCompressedHistoryFactory::addDeltaEntry(Int_t quote, Int_t depth)
{
	Delta * delta = (Delta *)chunk.deltas.Last();
	assert(numDeltaEntries <= delta->depths.GetSize());
	if (numDeltaEntries == delta->depths.GetSize())
	{
		delta->quotes.Set(numDeltaEntries * 2);
		delta->depths.Set(numDeltaEntries * 2);
	}
	delta->quotes[numDeltaEntries - 1] = quote;
	delta->depths[numDeltaEntries] = depth;

	++ numDeltaEntries;

	lastQuote += quote;
	runningDepths[lastQuote] += depth;
}
