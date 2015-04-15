#ifndef _BITSTAMPAPI_H_
#define _BITSTAMPAPI_H_

#include <string>
#include <sstream>
#include <curlpp/Easy.hpp>
#include <curlpp/cURLpp.hpp>

namespace bitstamp {

class api {
public:
	api(const std::string& key="", const std::string& userid = "", const std::string& secret = "");
	api(const api&);
	std::string ticker();
	std::string order_book();
	std::string balance();
	std::string orders();
	std::string transactions(const std::string& offset = "0", const std::string& limit = "1", const std::string& sort = "desc");
	std::string sell(const std::string& amount, const std::string& price);
	std::string buy(const std::string& amount, const std::string& price);
	std::string bitcoin_withdrawal(const std::string& amount, const std::string& address);
	std::string cancel(const std::string& order);
	std::string unconfirmed_btc();
	std::string bitcoin_deposit_address();
	std::string withdrawal_requests();

protected:
	std::string get_nonce();
	std::string get_auth();
	std::string https_get(const std::string& api);
	std::string https_post(const std::string& api, const std::string& post);

protected:
	std::string key_;
	std::string userid_;
	std::string secret_;
	curlpp::Cleanup cleaner_;
	curlpp::Easy getrequest_;
	curlpp::Easy postrequest_;
};

}
#endif
