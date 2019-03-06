#pragma once

#include <TArrayI.h>

struct OrderbookCompressedHistoryDelta : public TObject
{
	Char_t timestamp; // change from previous timestamp
	Long64_t baseQuote;
	TArrayI quotes; // run-length-encoded quotes: each is a delta from previous quote value, starting at base
	TArrayI depths; // delta from previous depths; can use multiple times if outside expected range

	// root
	OrderbookCompressedHistoryDelta();
	bool IsFolder() const { return kTRUE; }
	ClassDef(OrderbookCompressedHistoryDelta,3) // Delta details used within OrderbookCompressedHistory
};
