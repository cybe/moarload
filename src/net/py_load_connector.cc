#include "py_load_connector.h"

#include "../log.h"
#include "../util.h"



PyLoadConnector::PyLoadConnector(const std::string& pyLoadHostname, const int pyLoadPort)
{
    pyLoadURL = "http://" + pyLoadHostname + ":" + util::intToString(pyLoadPort) + "/api/";
    login("buildserver", "buildserver");

    //LOG(logINFO) << testClient.httpGet("http://zi0n.homelinux.net:8081/login");
}

PyLoadConnector::~PyLoadConnector()
{
    //dtor
}

void PyLoadConnector::login(const std::string& username, const std::string& password)
{
    HeaderEntry contentType;
    contentType.name = "Content-Type";
    contentType.value = "application/x-www-form-urlencoded";

    std::vector<HeaderEntry> additionalHeader;
    additionalHeader.push_back(contentType);

    LOG(logINFO) << client.httpPost(pyLoadURL + "login", "username=" + username + "&password=" + password, additionalHeader);


}
