#include "py_load_connector.h"

#include "../log.h"
#include "../util.h"

#include <map>


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
    using namespace std;
    multimap<string, string> additionalHeader;
    additionalHeader.insert(pair<string, string>("Content-Type", "application/x-www-form-urlencoded"));

    HttpRequest httpRequest;
    httpRequest.method = POST;
    httpRequest.url = pyLoadURL + "login";
    httpRequest.header = additionalHeader;
    httpRequest.data = "username=" + username + "&password=" + password;

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);
    LOG(logIO) << httpResponse.body;
}
