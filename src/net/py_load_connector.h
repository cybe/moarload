#ifndef PY_LOAD_CONNECTOR_H
#define PY_LOAD_CONNECTOR_H

#include <string>

#include "../lib/json/json-forwards.h"
#include "http_client.h"

struct ServerStatus
{
    bool pause;
    int active;
    int queue;
    int total;
    long long int speed;
    bool download;
    bool reconnect;
};



class PyLoadConnector
{
public:
    PyLoadConnector(const std::string& pyLoadHostname,
                    const int pyLoadPort,
                    const std::string& username,
                    const std::string& password);
    virtual ~PyLoadConnector();

    std::string getServerVersion();
    ServerStatus statusServer();
protected:
private:
    HttpClient httpClient;
    std::string pyLoadURL;
    std::string username;
    std::string password;

    void login();
};

#endif // PY_LOAD_CONNECTOR_H
