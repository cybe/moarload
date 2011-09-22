#include "moarload_net.h"

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#include <boost/optional.hpp>
#endif
#include <boost/network/protocol/http/client.hpp>

Net::Net()
{
    using namespace boost::network;
    http::client client;
    http::client::request request("http://google.de/");
    request << header("Connection", "close");
    http::client::response response = client.get(request);
    std::cout << body(response) << std::endl;
}

Net::~Net()
{
    //dtor
}
