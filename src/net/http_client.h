#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <map>

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#include <boost/optional.hpp>
#endif
#include <boost/network/protocol/http/client.hpp>

enum Method {GET, POST};

struct HttpRequest
{
    Method method;
    std::string url;
    std::multimap<std::string, std::string> header;
    std::string data;
};

struct HttpResponse
{
    std::multimap<std::string, std::string> header;
    std::string body;
};


class HttpClient
{
public:
    HttpClient();
    virtual ~HttpClient();
    HttpResponse dispatch(const HttpRequest& httpRequest);

protected:
private:
    boost::network::http::client client;

    std::multimap<std::string, std::string> parseHeader(const boost::network::http::client::response& response);
};

#endif // HTTP_CLIENT_H
