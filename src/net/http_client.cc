#include "http_client.h"

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#include <boost/optional.hpp>
#endif
#include <boost/network/protocol/http/client.hpp>

HttpClient::HttpClient()
{
    using namespace boost::network;
    http::client client;
    http::client::request request_("http://checkip.dyndns.com/");
    request_ << header("Connection", "close");
    http::client::response response_ = client.get(request_);
    requestBody = body(response_);
    std::cout << requestBody << std::endl;
}

HttpClient::~HttpClient()
{
    //dtor
}

std::string HttpClient::getBody()
{
    return requestBody;
}
