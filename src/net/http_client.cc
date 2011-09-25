#include "http_client.h"

HttpClient::HttpClient()
{




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
std::string HttpClient::httpPost(const std::string& url, const std::string& data)
{
    using namespace boost::network;
    http::client::request request_(url);
    http::client::response response_ = client_.post(request_, "application/json", data);
    return body(response_);
}


