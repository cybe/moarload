#include "http_client.h"

#include <boost/algorithm/string.hpp>

#include "../util.h"
#include "../log.h"

HttpClient::HttpClient()
{
    //ctor
}

HttpClient::~HttpClient()
{
    //dtor
}

HttpResponse HttpClient::dispatch(const HttpRequest& httpRequest)
{
    using namespace boost::network;

    http::client::request request(httpRequest.url);

    for (std::multimap<std::string, std::string>::const_iterator it = httpRequest.header.begin();
            it != httpRequest.header.end();
            ++it)
    {
        request << header(it->first, it->second);
    }

    if (httpRequest.data.length() > 0)
    {
        request << header("Content-Length", util::intToString(httpRequest.data.length()));
        request << body(httpRequest.data);
    }

    http::client::response response;

    switch (httpRequest.method)
    {
        case GET:
            LOG(logDEBUG) << "using get";
            response = client.get(request);
            break;
        case POST:
            LOG(logDEBUG) << "using post";
            response = client.post(request);
            break;
        default:
            LOG(logWARNING) << "unknown http method or method not set, using GET as fallback";
            response = client.get(request);
            break;
    }

    HttpResponse httpResponse;
    httpResponse.header = parseHeader(response);
    httpResponse.body = body(response);

    saveCookies(httpResponse.header);

    return httpResponse;
}

std::multimap<std::string, std::string> HttpClient::parseHeader(const boost::network::http::client::response& response)
{
    std::multimap<std::string, std::string> header;

    typedef boost::network::headers_range<boost::network::http::client::response>::type ResponseHeaders;
    boost::range_iterator<ResponseHeaders>::type it;
    ResponseHeaders responseHeaders = headers(response);
    for (it = responseHeaders.begin(); it != responseHeaders.end(); ++it)
    {
        std::string name = it->first;
        boost::algorithm::to_lower(name);
        header.insert(std::pair<std::string, std::string>(name, it->second));
    }

    return header;
}

void HttpClient::saveCookies(const std::multimap<std::string, std::string>& header)
{
    if (header.find("set-cookie") != header.end())
    {
        std::pair<std::multimap<std::string, std::string>::const_iterator, std::multimap<std::string, std::string>::const_iterator> range;
        range = header.equal_range("set-cookie");
        for (std::multimap<std::string, std::string>::const_iterator cookieString = range.first;
                cookieString != range.second;
                ++cookieString)
        {
            cookies.push_back(Cookie::parse(cookieString->second));
        }
    }
}
