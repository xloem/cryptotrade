#include <iomanip>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>
#include <errno.h>
#include "hmac.h"
#include "bitstampapi.h"

namespace bitstamp {

static const std::string BITSTAMP_API_URL = "https://www.bitstamp.net/api/";

api::api(const std::string& key, const std::string& userid, const std::string& secret)
	: key_{key}
	, userid_{userid}
	, secret_{secret}
{
}

api::api(const api& a)
	: key_{a.key_}
	, userid_{a.userid_}
	, secret_{a.secret_}
{
}

std::string api::get_nonce()
{
	std::stringstream oss;
	timespec now;
	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		oss << "clock_gettime failed, error code: " << errno;
		throw std::runtime_error(oss.str());
	}
	oss << now.tv_sec;
	oss.fill('0');
	oss << std::setw(6) << (now.tv_nsec / 1000);
	return oss.str();
}

std::string api::get_auth()
{
	std::stringstream oss;
	std::string nonce = get_nonce();
	std::string msg = nonce + userid_ + key_;
	oss << "key=" << key_ << "&";
	oss << "nonce=" << nonce << "&";
	oss << "signature=" << hmac_hex(secret_, msg);
	return oss.str();
}

std::string api::https_get(const std::string& api)
{
	std::stringstream oss;
	curlpp::options::WriteStream ws(&oss);
	getrequest_.setOpt(ws);
	getrequest_.setOpt<curlpp::options::Url>(BITSTAMP_API_URL + api);
	getrequest_.perform();
	return oss.str();
}

std::string api::https_post(const std::string& api, const std::string& post)
{
	std::stringstream oss;
	curlpp::options::WriteStream ws(&oss);
	postrequest_.setOpt(ws);
	postrequest_.setOpt<curlpp::options::Url>(BITSTAMP_API_URL + api);
	postrequest_.setOpt(curlpp::options::PostFields(post));
	postrequest_.perform();
	return oss.str();
}


std::string api::ticker()
{
	return https_get("ticker/");
}

std::string api::order_book()
{
	return https_get("order_book/");
}

std::string api::balance()
{
	return https_post("balance/", get_auth());
}

std::string api::unconfirmed_btc()
{
	return https_post("unconfirmed_btc/", get_auth());
}

std::string api::bitcoin_deposit_address()
{
	return https_post("bitcoin_deposit_address/", get_auth());
}

std::string api::orders()
{
	return https_post("open_orders/", get_auth());
}

std::string api::withdrawal_requests()
{
	return https_post("withdrawal_requests/", get_auth());
}

std::string api::transactions(const std::string& offset, const std::string& limit, const std::string& sort)
{
	std::stringstream post;
	post << get_auth() << "&offset=" << offset << "&limit=" << limit << "&sort=" << sort;
	return https_post("user_transactions/", post.str());
}

std::string api::sell(const std::string& amount, const std::string& price)
{
	std::stringstream post;
	post << get_auth() << "&amount=" << amount << "&price=" << price;
	return https_post("sell/", post.str());
}

std::string api::buy(const std::string& amount, const std::string& price)
{
	std::stringstream post;
	post << get_auth() << "&amount=" << amount << "&price=" << price;
	return https_post("buy/", post.str());
}

std::string api::bitcoin_withdrawal(const std::string& amount, const std::string& address)
{
	std::stringstream post;
	post << get_auth() << "&amount=" << amount << "&address=" << address;
	return https_post("bitcoin_withdrawal/", post.str());
}

std::string api::cancel(const std::string& order)
{
	std::stringstream post;
	post << get_auth() << "&id=" << order;
	return https_post("cancel_order/", post.str());
}


}
