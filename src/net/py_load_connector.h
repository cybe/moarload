#ifndef PY_LOAD_CONNECTOR_H
#define PY_LOAD_CONNECTOR_H

#include <string>

#include "http_client.h"


class PyLoadConnector
{
    public:
        PyLoadConnector(const std::string& pyLoadHostname, const int pyLoadPort);
        virtual ~PyLoadConnector();
    protected:
    private:
        HttpClient client;
        std::string pyLoadURL;
        std::string sessionID;

        void login(const std::string& username, const std::string& password);
};

#endif // PY_LOAD_CONNECTOR_H
