#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient
{
public:
    HttpClient();
    virtual ~HttpClient();
    std::string getBody();

protected:
private:
    std::string requestBody;
};

#endif // HTTP_CLIENT_H
