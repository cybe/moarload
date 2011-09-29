#ifndef PY_LOAD_CONNECTOR_H
#define PY_LOAD_CONNECTOR_H

#include <string>

#include "http_client.h"


class PyLoadConnector
{
public:
    PyLoadConnector(const std::string& pyLoadHostname,
                    const int pyLoadPort,
                    const std::string& username,
                    const std::string& password);
    virtual ~PyLoadConnector();

    std::string getServerVersion();
protected:
private:
    HttpClient httpClient;
    std::string pyLoadURL;
    std::string username;
    std::string password;

    void login();
};

#endif // PY_LOAD_CONNECTOR_H
