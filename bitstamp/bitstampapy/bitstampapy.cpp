#include <boost/python.hpp>
#include <sstream>
#include "api/bitstampapi.h"
using namespace boost::python;

BOOST_PYTHON_MODULE(bitstampapy)
{
	class_<bitstamp::api> b("api");
	b.def(init<const std::string&,const std::string&,const std::string&>());
	b.def("ticker", &bitstamp::api::ticker);
	b.def("balance", &bitstamp::api::balance);
	b.def("order_book", &bitstamp::api::order_book);
	b.def("orders", &bitstamp::api::orders);
	b.def("transactions", &bitstamp::api::transactions);
	b.def("sell", &bitstamp::api::sell);
	b.def("buy", &bitstamp::api::buy);
	b.def("bitcoin_withdrawal", &bitstamp::api::bitcoin_withdrawal);
	b.def("cancel", &bitstamp::api::cancel);
	b.def("unconfirmed_btc", &bitstamp::api::unconfirmed_btc);
	b.def("bitcoin_deposit_address", &bitstamp::api::bitcoin_deposit_address);
	b.def("withdrawal_requests", &bitstamp::api::withdrawal_requests);
}
