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

std::string PyLoadConnector::getServerVersion()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = pyLoadURL + "getServerVersion";

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
        << reader.getFormatedErrorMessages();
    }

    return root.asString();
}

ServerStatus PyLoadConnector::statusServer()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = pyLoadURL + "statusServer";

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
        << reader.getFormatedErrorMessages();
    }

    ServerStatus serverStatus;
    serverStatus.active = root["active"].asInt();
    serverStatus.download = root["download"].asBool();
    serverStatus.pause = root["pause"].asBool();
    serverStatus.queue = root["queue"].asInt();
    serverStatus.reconnect = root["reconnect"].asBool();
    serverStatus.speed = root["speed"].asInt64();
    serverStatus.total = root["total"].asInt();
    return serverStatus;
}
