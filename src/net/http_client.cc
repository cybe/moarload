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
    http::client::request request_(httpRequest.url);

    std::vector<HeaderEntry>::const_iterator entry;
    for (entry = httpRequest.header.begin();
         entry != httpRequest.header.end();
         ++entry)
    {
        request_ << header(entry->name, entry->value);
    }

    if (httpRequest.data.length() > 0)
    {
        request_ << header("Content-Length", util::intToString(httpRequest.data.length()));
        request_ << body(httpRequest.data);
    }

    http::client::response response;

    switch (httpRequest.method)
    {
        case GET:
            LOG(logDEBUG) << "using get";
            response = client_.get(request_);
            break;
        case POST:
            LOG(logDEBUG) << "using post";
            response = client_.post(request_);
            break;
        default:
            LOG(logWARNING) << "unknown http method or method not set, using GET as fallback";
            response = client_.get(request_);
            break;
    }

    HttpResponse httpResponse;
    httpResponse.header = parseHeader(response);
    httpResponse.body = body(response);

    return httpResponse;
}

std::vector<HeaderEntry> HttpClient::parseHeader(const boost::network::http::client::response& response)
{
    std::vector<HeaderEntry> entries;

    typedef boost::network::headers_range<boost::network::http::client::response>::type response_headers;
    boost::range_iterator<response_headers>::type it;
    response_headers headers_ = headers(response);
    for (it = headers_.begin(); it != headers_.end(); ++it)
    {
        HeaderEntry entry;
        entry.name = it->first;
        entry.value = it->second;
        entries.push_back(entry);
    }

    return entries;
}

