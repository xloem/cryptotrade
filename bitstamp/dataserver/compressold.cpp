#include "OrderbookCompressedHistory.hpp"

#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <iostream>

int main(int argc, char const ** argv)
{
	if (argc != 4)
	{
		std::cout << "Usage: " << argv[0] << " 'filepattern' objectname outputfile" << std::endl;
		return 1;
	}
	char const * pat = argv[1];
	char const * obj = argv[2];
	char const * output = argv[3];
	TChain ch(obj);
	ch.Add(pat);
	{
		TTreeReader reader(&ch);
		OrderbookCompressedHistory och;
		OrderbookCompressedHistoryFactory ochf(och);
		TTreeReaderValue<Double_t> rTime(reader, "time"), rQuote(reader, "quote"), rDepth(reader, "depth");
	
		std::cout << "Reading values ..." << std::endl;
		while(reader.Next())
		{
			ochf.advance(*rTime + 0.5);
			ochf.addEntry(*rQuote * 100 + 0.5, *rDepth * 100000000 + 0.5);
		}
		ochf.finishEntry();
	
		std::cout << "Writing output ..." << std::endl;
		TFile f(output, "NEW", "Orderbook History", 9);
		TTree t(obj, ch.GetTitle());
		t.Branch("compressedhistory", &och, 64 * 1024 * 1024, 0)->Fill();
		t.Write();
	}
	{
		TFile f(output);
		TTree * t = (TTree *)f.Get(obj);
		TTreeReader reader(&ch);
		OrderbookCompressedHistory * ochp;
		TTreeReaderValue<Double_t> rTime(reader, "time"), rQuote(reader, "quote"), rDepth(reader, "depth");

		t->SetBranchAddress("compressedhistory", &ochp);
		t->GetEntry(0);

		std::cout << "Comparing values ..." << std::endl;
		auto it = ochp->begin();
		while(reader.Next())
		{
			if (!(it != ochp->end()))
			{
				std::cout << "compressed file ends early" << std::endl;
				return -1;
			}
			auto timeQuoteDepth = *it;
			decltype(timeQuoteDepth) cmp{*rTime + 0.5, *rQuote * 100 + 0.5, *rDepth * 100000000 + 0.5};
			if (timeQuoteDepth != cmp)
			{
				std::cout << "Comparison failed =(" << std::endl;
				return -1;
			}
		}
		if (it != ochp->end())
		{
			std::cout << "extra values in compressed file" << std::endl;
			return -1;
		}
	}
}
