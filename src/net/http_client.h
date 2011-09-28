#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#include <boost/optional.hpp>
#endif
#include <boost/network/protocol/http/client.hpp>

enum Method {GET, POST};

struct HeaderEntry
{
    std::string name;
    std::string value;
};

struct HttpRequest
{
    Method method;
    std::string url;
    std::vector<HeaderEntry> header;
    std::string data;
};

struct HttpResponse
{
    std::vector<HeaderEntry> header;
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
    boost::network::http::client client_;

    std::vector<HeaderEntry> parseHeader(const boost::network::http::client::response& response);
};

#endif // HTTP_CLIENT_H
