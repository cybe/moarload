#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#include <boost/optional.hpp>
#endif
#include <boost/network/protocol/http/client.hpp>

class HttpClient
{
public:
    HttpClient();
    virtual ~HttpClient();
    std::string httpGet(const std::string& url);
    std::string httpPost(const std::string& url, const std::string& data);

protected:
private:
    boost::network::http::client client_;


};

#endif // HTTP_CLIENT_H
