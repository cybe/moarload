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
    http::client client_;
    http::client::request request_("http://checkip.dyndns.com/");
    http::client::response response_ = client_.get(request_);
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
