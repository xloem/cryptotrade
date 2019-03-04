#pragma once

#include <map>

#include <TObjArray.h>

#include "OrderbookCompressedHistoryDelta.hpp"

// key pieces:
//   - convert from ttree with branches to this
//   - convert from this to something graphable like back to the ttree (at least vectors of values)
//   - generate this from the network

struct OrderbookCompressedHistory : public TObject
{
public:
	OrderbookCompressedHistory() {}

	Long64_t entries();

	Long64_t baseTimestamp;
	TObjArray deltas;

	using Delta = OrderbookCompressedHistoryDelta;

	class Iterator
	{
	friend class OrderbookCompressedHistory;
	public:
		std::tuple<Long64_t, Long64_t, Long64_t> const & operator*() const;
		Iterator & operator++();
		bool operator!=(Iterator const & other);

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

	// root
	bool IsFolder() { return kTRUE; }
	ClassDef(OrderbookCompressedHistory,1) // slimmed-down storage for orderbook history
};

class OrderbookCompressedHistoryFactory
{
public:
	OrderbookCompressedHistoryFactory(OrderbookCompressedHistory & chunk);

	// must be filled in order
	void advance(Long64_t timestamp);
	void addEntry(Long64_t quote, Long64_t depth);
	void addChunk(OrderbookCompressedHistory & chunk);

	// will be auto-called as timestamp advances but should be called when done
	void finishEntry();

private:
	using Delta = OrderbookCompressedHistoryDelta;

	void addDeltaEntry(Int_t quote, Int_t depth);

	OrderbookCompressedHistory & chunk;
	Long64_t lastTimestamp;

	std::map<Long64_t,Long64_t> runningDepths;
	Int_t numDeltaEntries;
	Long64_t lastQuote;
};
