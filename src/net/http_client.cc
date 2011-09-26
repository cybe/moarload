#include "http_client.h"

#include "../util.h"

HttpClient::HttpClient()
{
    //ctor
}

HttpClient::~HttpClient()
{
    //dtor
}

/** @brief httpGet
  *
  * @todo: document this function
  */
std::string HttpClient::httpGet(const std::string& url)
{
    using namespace boost::network;
    http::client::request request_(url);
    http::client::response response_ = client_.get(request_);
    return body(response_);
}

/** @brief httpPost
  *
  * @todo: document this function
  */
std::string HttpClient::httpPost(const std::string& url, const std::string& data, const std::vector<HeaderEntry>& additionalHeader)
{
    using namespace boost::network;
    http::client::request request_(url);

    std::vector<HeaderEntry>::const_iterator entry;
    for (entry = additionalHeader.begin();
         entry != additionalHeader.end();
         ++entry)
    {
        request_ << header(entry->name, entry->value);
    }

    request_ << header("Content-Length", util::intToString(data.length()));
    request_ << body(data);
    http::client::response response_ = client_.post(request_);
    return body(response_);
}


