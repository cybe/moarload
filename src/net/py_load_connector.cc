#include "py_load_connector.h"

#include "../log.h"
#include "../util.h"
#include "../lib/json/json.h"

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
}

Json::Value* PyLoadConnector::getServerVersion()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = pyLoadURL + "getServerVersion";

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value* root = new Json::Value(); // del in:
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, *root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
                      << reader.getFormatedErrorMessages();
    }
    return root;
}

Json::Value* PyLoadConnector::statusServer()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = pyLoadURL + "statusServer";

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value* root = new Json::Value(); // del in:
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, *root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
                      << reader.getFormatedErrorMessages();
    }
    return root;
}
