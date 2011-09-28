#include "py_load_connector.h"

#include "../log.h"
#include "../util.h"



PyLoadConnector::PyLoadConnector(const std::string& pyLoadHostname,
                                 const int pyLoadPort,
                                 const std::string& username,
                                 const std::string& password)
    : username(username), password(password)
{
    pyLoadURL = "http://" + pyLoadHostname + ":" + util::intToString(pyLoadPort) + "/api/";
    login();
}

PyLoadConnector::~PyLoadConnector()
{
    //dtor
}

void PyLoadConnector::login()
{
    HeaderEntry contentType;
    contentType.name = "Content-Type";
    contentType.value = "application/x-www-form-urlencoded";

    std::vector<HeaderEntry> additionalHeader;
    additionalHeader.push_back(contentType);

    HttpRequest httpRequest;
    httpRequest.method = POST;
    httpRequest.url = pyLoadURL + "login";
    httpRequest.header = additionalHeader;
    httpRequest.data = "username=" + username + "&password=" + password;

    HttpResponse httpResponse = client.dispatch(httpRequest);
    LOG(logIO) << httpResponse.body;
}
