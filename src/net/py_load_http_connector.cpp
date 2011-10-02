#include "py_load_http_connector.h"

#include "../log.h"
#include "../util.h"
#include "../lib/json/json.h"

#include <map>


PyLoadHttpConnector::PyLoadHttpConnector(const std::string& hostname,
                                         const int port) :
    url("http://" + hostname + ":" + util::intToString(port) + "/api/")
{
}

PyLoadHttpConnector::~PyLoadHttpConnector()
{
    //dtor
}

bool PyLoadHttpConnector::login(const std::string& username, const std::string& password)
{
    using namespace std;
    multimap<string, string> additionalHeader;
    additionalHeader.insert(pair<string, string>("Content-Type", "application/x-www-form-urlencoded"));

    HttpRequest httpRequest;
    httpRequest.method = POST;
    httpRequest.url = url + "login";
    httpRequest.header = additionalHeader;
    httpRequest.data = "username=" + username + "&password=" + password;

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
                      << reader.getFormatedErrorMessages();
    }

    return root.asBool();
}

std::string PyLoadHttpConnector::getServerVersion()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = url + "getServerVersion";

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

ServerStatus_ PyLoadHttpConnector::statusServer()
{
    HttpRequest httpRequest;
    httpRequest.method = GET;
    httpRequest.url = url + "statusServer";

    HttpResponse httpResponse = httpClient.dispatch(httpRequest);

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(httpResponse.body, root);
    if (!parsingSuccessful)
    {
        LOG(logERROR) << "Failed to parse input:\n"
                      << reader.getFormatedErrorMessages();
    }

    ServerStatus_ serverStatus;
    serverStatus.active = root["active"].asInt();
    serverStatus.download = root["download"].asBool();
    serverStatus.pause = root["pause"].asBool();
    serverStatus.queue = root["queue"].asInt();
    serverStatus.reconnect = root["reconnect"].asBool();
    serverStatus.speed = root["speed"].asInt64();
    serverStatus.total = root["total"].asInt();
    return serverStatus;
}
