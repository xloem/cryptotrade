#include "OrderbookCompressedHistory.hpp"

#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <iostream>

template <typename F>
void iterateTimeQuoteDepth(std::string obj, std::string pat, F const & f)
{
	TChain ch(obj.c_str());
	ch.Add(pat.c_str());
	TTreeReader reader(&ch);
	TTreeReaderValue<Double_t> rTime(reader, "time"), rQuote(reader, "quote"), rDepth(reader, "depth");

	std::map<Long64_t, Long64_t> curDepths;
	bool keepgoing = reader.Next();

	while (keepgoing)
	{
		Long64_t lastTime = *rTime + 0.5;
		Long64_t nextTime = lastTime;
		curDepths.clear();
		do
		{
			curDepths[*rQuote * 100 + 0.5] = *rDepth * 100000000 + 0.5;
			keepgoing = reader.Next();
			if (!keepgoing)
			{
				break;
			}
			nextTime = *rTime + 0.5;
		}
		while (nextTime == lastTime);

		for (auto & quoteDepth : curDepths)
		{
			f(lastTime, quoteDepth.first, quoteDepth.second);
		}
	}
}

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
	
		std::cout << "Reading values ..." << std::endl;
		iterateTimeQuoteDepth(obj, pat,
				[&](Long64_t time, Long64_t quote, Long64_t depth)
				{
					ochf.advance(time);
					ochf.addEntry(quote, depth);
				}
				);
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
		OrderbookCompressedHistory * ochp = nullptr;
		TTreeReaderValue<Double_t> rTime(reader, "time"), rQuote(reader, "quote"), rDepth(reader, "depth");

		auto branch = t->GetBranch("compressedhistory");
		branch->SetAddress(&ochp);
		branch->GetEntry(0);

		std::cout << "Comparing values ..." << std::endl;
		auto it = ochp->begin();
		std::map<Long64_t,Long64_t> runningDepths;
		iterateTimeQuoteDepth(obj, pat,
				[&](Long64_t time, Long64_t quote, Long64_t depth)
				{
					if (runningDepths[quote] == depth)
					{
						return;
					}
					//std::cout << "Data:  " << time << " " << quote << " " << depth << std::endl;
					if (!(it != ochp->end()))
					{
						std::cout << "compressed file ends early" << std::endl;
						exit(-1);
					}
					std::tuple<Long64_t,Long64_t,Long64_t> cmp{time, quote, depth};
					std::tuple<Long64_t,Long64_t,Long64_t> timeQuoteDepth = *it;
					++ it;
					if (timeQuoteDepth != cmp)
					{
						std::cout << "Comparison failed =(" << std::endl;
						std::cout << "Previous:             " << quote << " " << runningDepths[quote] << std::endl;
						std::cout << "Original:  " << time << " " << quote << " " << depth << std::endl;
						std::cout << "Reencoded: " << std::get<0>(timeQuoteDepth) << " " << std::get<1>(timeQuoteDepth) << " " << std::get<2>(timeQuoteDepth) << std::endl; 
						exit(-1);
					}
					runningDepths[quote] = depth;
				}
		);
		if (it != ochp->end())
		{
			std::cout << "extra values in compressed file" << std::endl;
			return -1;
		}
	}
	std::cout << "Success." << std::endl;
	return 0;
}
