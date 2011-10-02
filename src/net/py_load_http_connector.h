#ifndef PY_LOAD_HTTP_CONNECTOR_H
#define PY_LOAD_HTTP_CONNECTOR_H

#include <string>

#include "../lib/json/json-forwards.h"
#include "http/http_client.h"

struct ServerStatus_
{
    bool pause;
    int active;
    int queue;
    int total;
    long long int speed;
    bool download;
    bool reconnect;
};



class PyLoadHttpConnector
{
public:
    PyLoadHttpConnector(const std::string& hostname,
                        const int port);
    virtual ~PyLoadHttpConnector();

    std::string getServerVersion();
    ServerStatus_ statusServer();
    bool login(const std::string& username, const std::string& password);
protected:
private:
    HttpClient httpClient;
    std::string url;
};

#endif // PY_LOAD_HTTP_CONNECTOR_H
