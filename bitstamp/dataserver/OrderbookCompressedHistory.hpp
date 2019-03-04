#pragma once

#include <map>

#include <TArrayI.h>
#include <TObjArray.h>

// key pieces:
//   - convert from ttree with branches to this
//   - convert from this to something graphable like back to the ttree (at least vectors of values)
//   - generate this from the network

struct OrderbookCompressedHistory
{
public:
	Long64_t entries();

	Long64_t baseTimestamp;
	TObjArray deltas;

	struct Delta : public TObject
	{
		UChar_t timestamp; // change from previous timestamp
		Long64_t baseQuote;
		TArrayI quotes; // run-length-encoded quotes: each is a delta from previous quote value, starting at base
		TArrayI depths; // delta from previous depths; can use multiple times if outside expected range
	};

	class Iterator
	{
	friend class OrderbookCompressedHistory;
	public:
		std::tuple<Long64_t, Long64_t, Long64_t> const & operator*() const;
		Iterator & operator++();
		bool operator!=(Iterator & other);

	private:
		Iterator(OrderbookCompressedHistory *obook);
		
		OrderbookCompressedHistory * obook;
		Int_t deltaIdx;
		Int_t entryIdx;
		std::tuple<Long64_t, Long64_t, Long64_t> timeQuoteDepth;
		std::map<Long64_t,Long64_t> depths;
	};

	// iterating provides 3-tuples of timestamp, quote, and depth
	Iterator begin() { return {this}; }
	Iterator end() { return {nullptr}; }
};

class OrderbookCompressedHistoryFactory
{
public:
	OrderbookCompressedHistoryFactory(OrderbookCompressedHistory & chunk);

	// must be filled in order
	void advance(Long64_t timestamp);
	void addEntry(Long64_t quote, Long64_t depth);
	void addChunk(OrderbookCompressedHistory & chunk);

private:
	using Delta = OrderbookCompressedHistory::Delta;

	void finishEntry();
	void addDeltaEntry(Int_t quote, Int_t depth);

	OrderbookCompressedHistory & chunk;
	Long64_t lastTimestamp;

	std::map<Long64_t,Long64_t> runningDepths;
	Int_t numDeltaEntries;
	Long64_t lastQuote;
};
