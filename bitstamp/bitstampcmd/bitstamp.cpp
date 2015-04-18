#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "cmdargs.h"
#include "rexjson/rexjson++.h"
#include "api/bitstampapi.h"


cmd_args g_args;

/*
 * Cmd args spec:
 * "argument name" "argument alias" "Help message"
 */
static cmd_arg_spec g_argspec[] = {
		{"help",	"h",	"Display this help", CMD_ARG_BOOL},
		{"config",	"",		"JSON Config file, containing: user, key, secret", CMD_ARG_STRING},
		{"user",	"",		"Bitstamp user id", CMD_ARG_STRING},
		{"key",		"",		"Bitstamp API key", CMD_ARG_STRING},
		{"secret",	"",		"Bitstamp API secret", CMD_ARG_STRING},
		{"offset",	"",		"Skip that many transactions before beginning to return results", CMD_ARG_STRING},
		{"limit",	"",		"Limit result to that many transactions", CMD_ARG_STRING},
		{"sort",	"",		"Sorting transactions by date and time (asc - ascending; desc - descending)", CMD_ARG_STRING},
		{"amount",	"",		"amount to buy/sell/withdraw", CMD_ARG_STRING},
		{"price",	"",		"price to buy/sell", CMD_ARG_STRING},
		{"address",	"",		"BTC withdrawal address", CMD_ARG_STRING},
		{"order",	"",		"order id to cancel", CMD_ARG_STRING},
};


void help(int argc, const char *argv[])
{
	std::cout << argv[0] << " [help|withdrawals|btcaddress|unconfirmed|orderbook|ticker|transactions|withdrawbtc|buy|sell|cancel] <options>" << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << g_args.get_help_message() << std::endl;
}

int main(int argc, const char *argv[])
{
	std::stringstream oss;
	rexjson::value v = rexjson::object();
	g_args.add_specs(g_argspec, sizeof(g_argspec)/sizeof(*g_argspec));

	try {
		g_args.parse_command_line(argc, argv);
	} catch (std::exception& e) {
		std::cout << "Incorect command line, got error: " << e.what() << std::endl;
		return 1;
	}
	if (!g_args.get_value("help").empty()) {
		help(argc, argv);
		return 0;
	}

	try {
		rexjson::value cfg = rexjson::object();
		if (!g_args.get_value("config").empty()) {
			std::ifstream ifs(g_args.get_value("config"));
			std::stringstream buffer;
			buffer << ifs.rdbuf();
			cfg.read(buffer.str());
		}
		if (!g_args.get_value("key").empty())
			cfg["key"] = g_args.get_value("key");
		if (!g_args.get_value("user").empty())
			cfg["user"] = g_args.get_value("user");
		if (!g_args.get_value("secret").empty())
			cfg["secret"] = g_args.get_value("secret");
		bitstamp::api api(cfg["key"].get_str(), cfg["user"].get_str(), cfg["secret"].get_str());
		for (int i = 1; i < argc; i++) {
			std::string arg(argv[i]);
			if (arg[0] == '-')
				continue;
			if (arg == "ticker") {
				std::cout << rexjson::read(api.ticker()).write(true) << std::endl;
				break;
			}else if (arg == "orderbook") {
				std::cout << rexjson::read(api.order_book()).write(true) << std::endl;
				break;
			}else if (arg == "withdrawals") {
				std::cout << rexjson::read(api.withdrawal_requests()).write(true) << std::endl;
				break;
			} else if (arg == "balance") {
				std::cout << rexjson::read(api.balance()).write(true) << std::endl;
				break;
			} else if (arg == "unconfirmed") {
				std::cout << rexjson::read(api.unconfirmed_btc()).write(true) << std::endl;
				break;
			} else if (arg == "orders") {
				std::cout << rexjson::read(api.orders()).write(true) << std::endl;
				break;
			} else if (arg == "btcaddress") {
				std::cout << rexjson::read(api.bitcoin_deposit_address()).write(true) << std::endl;
				break;
			} else if (arg == "transactions") {
				std::string offset = g_args.get_value("offset", "0");
				std::string limit = g_args.get_value("limit", "1");
				std::string sort = g_args.get_value("sort", "desc");
				std::cout << rexjson::read(api.transactions(offset, limit, sort)).write(true) << std::endl;
				break;
			} else if (arg == "withdrawbtc") {
				std::string amount = g_args.get_value("amount");
				std::string address = g_args.get_value("address");
				if (amount.empty() || address.empty()) {
					std::cout << "Invalid BTC withdrawal parameters" << std::endl;
					return 1;
				}
				std::cout << rexjson::read(api.bitcoin_withdrawal(amount, address)).write(true) << std::endl;
				break;
			} else if (arg == "buy") {
				std::string amount = g_args.get_value("amount");
				std::string price = g_args.get_value("price");
				if (amount.empty() || price.empty()) {
					std::cout << "Invalid order parameters" << std::endl;
					return 1;
				}
				std::cout << rexjson::read(api.buy(amount, price)).write(true) << std::endl;
				break;
			} else if (arg == "sell") {
				std::string amount = g_args.get_value("amount");
				std::string price = g_args.get_value("price");
				if (amount.empty() || price.empty()) {
					std::cout << "Invalid order parameters" << std::endl;
					return 1;
				}
				std::cout << rexjson::read(api.sell(amount, price)).write(true) << std::endl;
				break;
			} else if (arg == "cancel") {
				std::string order = g_args.get_value("order");
				if (order.empty()) {
					std::cout << "Invalid order parameters" << std::endl;
					return 1;
				}
				std::cout << rexjson::read(api.cancel(order)).write(true) << std::endl;
				break;
			} else if (arg == "help") {
				help(argc, argv);
				break;
			} else {
				std::cout << arg << " is invalid command" << std::endl;
				break;
			}
		}
		return 0;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
