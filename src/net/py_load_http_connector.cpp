#include "py_load_http_connector.h"

#include <map>

#include "../log.h"
#include "../util.h"
#include "../lib/json/json.h"


PyLoadHttpConnector::PyLoadHttpConnector(const std::string& hostname,
                                         const unsigned short port) :
    url("http://" + hostname + ":" + util::intToString(port) + "/api/")
{
}

PyLoadHttpConnector::~PyLoadHttpConnector()
{
    //dtor
}

void PyLoadHttpConnector::getConfigValue(std::string& _return, const std::string& category, const std::string& option, const std::string& section)
{
    return;
}

void PyLoadHttpConnector::setConfigValue(const std::string& category, const std::string& option, const std::string& value, const std::string& section)
{
    return;
}

void PyLoadHttpConnector::getConfig(std::map<std::string, ConfigSection> & _return)
{
    return;
}

void PyLoadHttpConnector::getPluginConfig(std::map<std::string, ConfigSection> & _return)
{
    return;
}

void PyLoadHttpConnector::pauseServer()
{
    return;
}

void PyLoadHttpConnector::unpauseServer()
{
    return;
}

bool PyLoadHttpConnector::togglePause()
{
    bool _return = false;
    return _return;
}

void PyLoadHttpConnector::statusServer(ServerStatus& _return)
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

    _return.active = root["active"].asInt();
    _return.download = root["download"].asBool();
    _return.pause = root["pause"].asBool();
    _return.queue = root["queue"].asInt();
    _return.reconnect = root["reconnect"].asBool();
    _return.speed = root["speed"].asInt64();
    _return.total = root["total"].asInt();
}

int64_t PyLoadHttpConnector::freeSpace()
{
    int64_t _return = 0;
    return _return;
}

void PyLoadHttpConnector::getServerVersion(std::string& _return)
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

    _return = root.asString();
}

void PyLoadHttpConnector::kill()
{
    return;
}

void PyLoadHttpConnector::restart()
{
    return;
}

void PyLoadHttpConnector::getLog(std::vector<std::string> & _return, const int32_t offset)
{
    return;
}

bool PyLoadHttpConnector::isTimeDownload()
{
    bool _return = false;
    return _return;
}

bool PyLoadHttpConnector::isTimeReconnect()
{
    bool _return = false;
    return _return;
}

bool PyLoadHttpConnector::toggleReconnect()
{
    bool _return = false;
    return _return;
}

void PyLoadHttpConnector::generatePackages(std::map<std::string, LinkList> & _return, const LinkList& links)
{
    return;
}

void PyLoadHttpConnector::checkURLs(std::map<PluginName, LinkList> & _return, const LinkList& urls)
{
    return;
}

void PyLoadHttpConnector::parseURLs(std::map<PluginName, LinkList> & _return, const std::string& html, const std::string& url)
{
    return;
}

void PyLoadHttpConnector::checkOnlineStatus(OnlineCheck& _return, const LinkList& urls)
{
    return;
}

void PyLoadHttpConnector::checkOnlineStatusContainer(OnlineCheck& _return, const LinkList& urls, const std::string& filename, const std::string& data)
{
    return;
}

void PyLoadHttpConnector::pollResults(OnlineCheck& _return, const ResultID rid)
{
    return;
}

void PyLoadHttpConnector::statusDownloads(std::vector<DownloadInfo> & _return)
{
    return;
}

void PyLoadHttpConnector::getPackageData(PackageData& _return, const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::getPackageInfo(PackageData& _return, const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::getFileData(FileData& _return, const FileID fid)
{
    return;
}

void PyLoadHttpConnector::getQueue(std::vector<PackageData> & _return)
{
    return;
}

void PyLoadHttpConnector::getCollector(std::vector<PackageData> & _return)
{
    return;
}

void PyLoadHttpConnector::getQueueData(std::vector<PackageData> & _return)
{
    return;
}

void PyLoadHttpConnector::getCollectorData(std::vector<PackageData> & _return)
{
    return;
}

void PyLoadHttpConnector::getPackageOrder(std::map<int16_t, PackageID> & _return, const Destination::type destination)
{
    return;
}

void PyLoadHttpConnector::getFileOrder(std::map<int16_t, FileID> & _return, const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::generateAndAddPackages(std::vector<PackageID> & _return, const LinkList& links, const Destination::type dest)
{
    return;
}

PackageID PyLoadHttpConnector::addPackage(const std::string& name, const LinkList& links, const Destination::type dest)
{
    PackageID _return = 0;
    return _return;
}

void PyLoadHttpConnector::addFiles(const PackageID pid, const LinkList& links)
{
    return;
}

void PyLoadHttpConnector::uploadContainer(const std::string& filename, const std::string& data)
{
    return;
}

void PyLoadHttpConnector::deleteFiles(const std::vector<FileID> & fids)
{
    return;
}

void PyLoadHttpConnector::deletePackages(const std::vector<PackageID> & pids)
{
    return;
}

void PyLoadHttpConnector::pushToQueue(const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::pullFromQueue(const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::restartPackage(const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::restartFile(const FileID fid)
{
    return;
}

void PyLoadHttpConnector::recheckPackage(const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::stopAllDownloads()
{
    return;
}

void PyLoadHttpConnector::stopDownloads(const std::vector<FileID> & fids)
{
    return;
}

void PyLoadHttpConnector::setPackageName(const PackageID pid, const std::string& name)
{
    return;
}

void PyLoadHttpConnector::movePackage(const Destination::type destination, const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::moveFiles(const std::vector<FileID> & fids, const PackageID pid)
{
    return;
}

void PyLoadHttpConnector::orderPackage(const PackageID pid, const int16_t position)
{
    return;
}

void PyLoadHttpConnector::orderFile(const FileID fid, const int16_t position)
{
    return;
}

void PyLoadHttpConnector::setPackageData(const PackageID pid, const std::map<std::string, std::string> & data)
{
    return;
}

void PyLoadHttpConnector::deleteFinished()
{
    return;
}

void PyLoadHttpConnector::restartFailed()
{
    return;
}

bool PyLoadHttpConnector::isCaptchaWaiting()
{
    bool _return = false;
    return _return;
}

void PyLoadHttpConnector::getCaptchaTask(CaptchaTask& _return, const bool exclusive)
{
    return;
}

void PyLoadHttpConnector::getCaptchaTaskStatus(std::string& _return, const TaskID tid)
{
    return;
}

void PyLoadHttpConnector::setCaptchaResult(const TaskID tid, const std::string& result)
{
    return;
}

void PyLoadHttpConnector::getEvents(std::vector<EventInfo> & _return, const std::string& uuid)
{
    return;
}

void PyLoadHttpConnector::getAccounts(std::vector<AccountInfo> & _return, const bool refresh)
{
    return;
}

void PyLoadHttpConnector::getAccountTypes(std::vector<std::string> & _return)
{
    return;
}

void PyLoadHttpConnector::updateAccount(const PluginName& plugin, const std::string& account, const std::string& password, const std::map<std::string, std::string> & options)
{
    return;
}

void PyLoadHttpConnector::removeAccount(const PluginName& plugin, const std::string& account)
{
    return;
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

void PyLoadHttpConnector::getUserData(UserData& _return, const std::string& username, const std::string& password)
{
    return;
}

void PyLoadHttpConnector::getAllUserData(std::map<std::string, UserData> & _return)
{
    return;
}

void PyLoadHttpConnector::getServices(std::map<PluginName, std::map<std::string, std::string> > & _return)
{
    return;
}

bool PyLoadHttpConnector::hasService(const PluginName& plugin, const std::string& func)
{
    bool _return = false;
    return _return;
}

void PyLoadHttpConnector::call(std::string& _return, const ServiceCall& info)
{
    return;
}

void PyLoadHttpConnector::getAllInfo(std::map<PluginName, std::map<std::string, std::string> > & _return)
{
    return;
}

void PyLoadHttpConnector::getInfoByPlugin(std::map<std::string, std::string> & _return, const PluginName& plugin)
{
    return;
}
