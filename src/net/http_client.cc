#include "http_client.h"

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
        header.insert(std::pair<std::string, std::string>(it->first, it->second));
    }

    return header;
}

