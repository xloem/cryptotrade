#include <TChain.h>
#include <TFile.h>
#include <TNtupleD.h>
#include <TSystem.h>
#include <TTimeStamp.h>

#include <csignal>
#include <iostream>

#include "rexjson/rexjson++.h"
#include "api/bitstampapi.h"

static bool stopped = false;

class Main
{
public:
	Main(std::string DATAOBJNAME)
	: DATAOBJNAME(DATAOBJNAME),
	  DATAFILNAME(DATAOBJNAME + "-" +
	    rexjson::read(bitstamp.ticker()).get_obj()["timestamp"].get_str()
	    + ".root"),
	  lastTimestamp(0)
	{
		stopped = false;
		std::signal(SIGINT, signal_quit);
		std::signal(SIGTERM, signal_quit);
		std::signal(SIGABRT, signal_quit);

		{
			TChain chain(DATAOBJNAME.c_str());
			std::string pat = DATAOBJNAME + "-*.root";
			chain.Add(pat.c_str());
			if (chain.GetEntries() > 0)
			{
				chain.SetBranchAddress("time", &lastTimestamp);
				chain.GetEntry(chain.GetEntries() - 1);
				std::cout << "Last entry was @" << lastTimestamp << std::endl;
			}
		}

		f = new TFile(DATAFILNAME.c_str(), "NEW", "Orderbook History", 9);
	  	nt = new TNtupleD(DATAOBJNAME.c_str(), "Bitstamp Orderbook Snapshot History", "time:quote:depth");
	}

	void pollSnapshot()
	{
		std::string result;
		try
		{
			result = bitstamp.order_book();
		}
		catch(curlpp::LibcurlRuntimeError e)
		{
			std::cout << "Error " << e.what() << std::endl;
			return;
		}
		auto obook = rexjson::read(result).get_obj();
		Double_t timestamp = std::stod(obook["timestamp"].get_str());
		if (timestamp == lastTimestamp && (lastResult == "" || lastResult == result))
		{
			std::cout << "Duplicate result, ignoring" << std::endl;
			return;
		}
		lastTimestamp = timestamp;
		lastResult = result;
		auto bids = obook["bids"].get_array();
		auto asks = obook["asks"].get_array();
		std::cout << DATAOBJNAME << " in " << DATAFILNAME << ": entry @" << timestamp << std::endl;
		// bids are offers to buy for a low price that will be filled by sellers
		// asks are offers to sell for a high price that will be filled by buyers
		for (auto & bidv : bids)
		{
			auto bida = bidv.get_array();
			Double_t quote = std::stod(bida[0].get_str());
			Double_t depth = std::stod(bida[1].get_str());
			nt->Fill(timestamp, quote, depth);
		}
		for (auto & askv: asks)
		{
			auto aska = askv.get_array();
			Double_t quote = std::stod(aska[0].get_str());
			Double_t depth = std::stod(aska[1].get_str());
			depth = -depth; // to represent an ask rather than a bid
			nt->Fill(timestamp, quote, depth);
		}
	}

	void writeOut()
	{
		std::cout << "Flushing to " << DATAFILNAME << std::endl;
		nt->Write();
		f->Flush();
	}

	void run(Long_t millisPoll, Long_t millisWrite)
	{
		TTimeStamp start;
		while (!stopped)
		{
			pollSnapshot();
			gSystem->Sleep(millisPoll);
			TTimeStamp now;
			if (now.GetSec() - start.GetSec() > millisWrite / 1000)
			{
				writeOut();
				start = now;
			}
		}
	}

	~Main()
	{
		writeOut();
		// nt is deleted when f is closed because it is in its directory
		f->Close();
		delete f;
	}

private:
	bitstamp::api bitstamp;
	std::string DATAOBJNAME;
	std::string DATAFILNAME;
	TFile * f;
	TNtupleD * nt;
	Double_t lastTimestamp;
	std::string lastResult;

	static void signal_quit(int x)
	{
		stopped = true;
	}
};

int main()
{
	std::cout << std::fixed;
	Main m("BitstampOrderbookHistory");
	m.run(5000, 10*60*1000);
	return 0;
}
