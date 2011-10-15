#include "py_load_thrift_connector.h"

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include "../log.h"

PyLoadThriftConnector::PyLoadThriftConnector(const std::string& hostname,
                                             const unsigned short port) :
    //transport(NULL),
    client(NULL) {
    using namespace apache::thrift;
    using namespace apache::thrift::protocol;
    using namespace apache::thrift::transport;

    boost::shared_ptr<TSocket> socket(new TSocket(hostname, port));
    transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    client = new PyloadClient(protocol);
    transport->open();
}

PyLoadThriftConnector::~PyLoadThriftConnector() {
    transport->close();
    delete client;
}

void PyLoadThriftConnector::getConfigValue(std::string& _return, const std::string& category, const std::string& option, const std::string& section) {
    return client->getConfigValue(_return, category, option, section);
}

void PyLoadThriftConnector::setConfigValue(const std::string& category, const std::string& option, const std::string& value, const std::string& section) {
    return client->setConfigValue(category, option, value, section);
}

void PyLoadThriftConnector::getConfig(std::map<std::string, ConfigSection> & _return) {
    return client->getConfig(_return);
}

void PyLoadThriftConnector::getPluginConfig(std::map<std::string, ConfigSection> & _return) {
    return client->getPluginConfig(_return);
}

void PyLoadThriftConnector::pauseServer() {
    return client->pauseServer();
}

void PyLoadThriftConnector::unpauseServer() {
    return client->unpauseServer();
}

bool PyLoadThriftConnector::togglePause() {
    return client->togglePause();
}

void PyLoadThriftConnector::statusServer(ServerStatus& _return) {
    return client->statusServer(_return);
}

int64_t PyLoadThriftConnector::freeSpace() {
    return client->freeSpace();
}

void PyLoadThriftConnector::getServerVersion(std::string& _return) {
    return client->getServerVersion(_return);
}

void PyLoadThriftConnector::kill() {
    return client->kill();
}

void PyLoadThriftConnector::restart() {
    return client->restart();
}

void PyLoadThriftConnector::getLog(std::vector<std::string> & _return, const int32_t offset) {
    return client->getLog(_return, offset);
}

bool PyLoadThriftConnector::isTimeDownload() {
    return client->isTimeDownload();
}

bool PyLoadThriftConnector::isTimeReconnect() {
    return client->isTimeReconnect();
}

bool PyLoadThriftConnector::toggleReconnect() {
    return client->toggleReconnect();
}

void PyLoadThriftConnector::generatePackages(std::map<std::string, LinkList> & _return, const LinkList& links) {
    return client->generatePackages(_return, links);
}

void PyLoadThriftConnector::checkURLs(std::map<PluginName, LinkList> & _return, const LinkList& urls) {
    return client->checkURLs(_return, urls);
}

void PyLoadThriftConnector::parseURLs(std::map<PluginName, LinkList> & _return, const std::string& html, const std::string& url) {
    return client->parseURLs(_return, html, url);
}

void PyLoadThriftConnector::checkOnlineStatus(OnlineCheck& _return, const LinkList& urls) {
    return client->checkOnlineStatus(_return, urls);
}

void PyLoadThriftConnector::checkOnlineStatusContainer(OnlineCheck& _return, const LinkList& urls, const std::string& filename, const std::string& data) {
    return client->checkOnlineStatusContainer(_return, urls, filename, data);
}

void PyLoadThriftConnector::pollResults(OnlineCheck& _return, const ResultID rid) {
    return client->pollResults(_return, rid);
}

void PyLoadThriftConnector::statusDownloads(std::vector<DownloadInfo> & _return) {
    return client->statusDownloads(_return);
}

void PyLoadThriftConnector::getPackageData(PackageData& _return, const PackageID pid) {
    return client->getPackageData(_return, pid);
}

void PyLoadThriftConnector::getPackageInfo(PackageData& _return, const PackageID pid) {
    return client->getPackageInfo(_return, pid);
}

void PyLoadThriftConnector::getFileData(FileData& _return, const FileID fid) {
    return client->getFileData(_return, fid);
}

void PyLoadThriftConnector::getQueue(std::vector<PackageData> & _return) {
    return client->getQueue(_return);
}

void PyLoadThriftConnector::getCollector(std::vector<PackageData> & _return) {
    return client->getCollector(_return);
}

void PyLoadThriftConnector::getQueueData(std::vector<PackageData> & _return) {
    return client->getQueueData(_return);
}

void PyLoadThriftConnector::getCollectorData(std::vector<PackageData> & _return) {
    return client->getCollectorData(_return);
}

void PyLoadThriftConnector::getPackageOrder(std::map<int16_t, PackageID> & _return, const Destination::type destination) {
    return client->getPackageOrder(_return, destination);
}

void PyLoadThriftConnector::getFileOrder(std::map<int16_t, FileID> & _return, const PackageID pid) {
    return client->getFileOrder(_return, pid);
}

void PyLoadThriftConnector::generateAndAddPackages(std::vector<PackageID> & _return, const LinkList& links, const Destination::type dest) {
    return client->generateAndAddPackages(_return, links, dest);
}

PackageID PyLoadThriftConnector::addPackage(const std::string& name, const LinkList& links, const Destination::type dest) {
    return client->addPackage(name, links, dest);
}

void PyLoadThriftConnector::addFiles(const PackageID pid, const LinkList& links) {
    return client->addFiles(pid, links);
}

void PyLoadThriftConnector::uploadContainer(const std::string& filename, const std::string& data) {
    return client->uploadContainer(filename, data);
}

void PyLoadThriftConnector::deleteFiles(const std::vector<FileID> & fids) {
    return client->deleteFiles(fids);
}

void PyLoadThriftConnector::deletePackages(const std::vector<PackageID> & pids) {
    return client->deletePackages(pids);
}

void PyLoadThriftConnector::pushToQueue(const PackageID pid) {
    return client->pushToQueue(pid);
}

void PyLoadThriftConnector::pullFromQueue(const PackageID pid) {
    return client->pullFromQueue(pid);
}

void PyLoadThriftConnector::restartPackage(const PackageID pid) {
    return client->restartPackage(pid);
}

void PyLoadThriftConnector::restartFile(const FileID fid) {
    return client->restartFile(fid);
}

void PyLoadThriftConnector::recheckPackage(const PackageID pid) {
    return client->recheckPackage(pid);
}

void PyLoadThriftConnector::stopAllDownloads() {
    return client->stopAllDownloads();
}

void PyLoadThriftConnector::stopDownloads(const std::vector<FileID> & fids) {
    return client->stopDownloads(fids);
}

void PyLoadThriftConnector::setPackageName(const PackageID pid, const std::string& name) {
    return client->setPackageName(pid, name);
}

void PyLoadThriftConnector::movePackage(const Destination::type destination, const PackageID pid) {
    return client->movePackage(destination, pid);
}

void PyLoadThriftConnector::moveFiles(const std::vector<FileID> & fids, const PackageID pid) {
    return client->moveFiles(fids, pid);
}

void PyLoadThriftConnector::orderPackage(const PackageID pid, const int16_t position) {
    return client->orderPackage(pid, position);
}

void PyLoadThriftConnector::orderFile(const FileID fid, const int16_t position) {
    return client->orderFile(fid, position);
}

void PyLoadThriftConnector::setPackageData(const PackageID pid, const std::map<std::string, std::string> & data) {
    return client->setPackageData(pid, data);
}

void PyLoadThriftConnector::deleteFinished() {
    return client->deleteFinished();
}

void PyLoadThriftConnector::restartFailed() {
    return client->restartFailed();
}

bool PyLoadThriftConnector::isCaptchaWaiting() {
    return client->isCaptchaWaiting();
}

void PyLoadThriftConnector::getCaptchaTask(CaptchaTask& _return, const bool exclusive) {
    return client->getCaptchaTask(_return, exclusive);
}

void PyLoadThriftConnector::getCaptchaTaskStatus(std::string& _return, const TaskID tid) {
    return client->getCaptchaTaskStatus(_return, tid);
}

void PyLoadThriftConnector::setCaptchaResult(const TaskID tid, const std::string& result) {
    return client->setCaptchaResult(tid, result);
}

void PyLoadThriftConnector::getEvents(std::vector<EventInfo> & _return, const std::string& uuid) {
    return client->getEvents(_return, uuid);
}

void PyLoadThriftConnector::getAccounts(std::vector<AccountInfo> & _return, const bool refresh) {
    return client->getAccounts(_return, refresh);
}

void PyLoadThriftConnector::getAccountTypes(std::vector<std::string> & _return) {
    return client->getAccountTypes(_return);
}

void PyLoadThriftConnector::updateAccount(const PluginName& plugin, const std::string& account, const std::string& password, const std::map<std::string, std::string> & options) {
    return client->updateAccount(plugin, account, password, options);
}

void PyLoadThriftConnector::removeAccount(const PluginName& plugin, const std::string& account) {
    return client->removeAccount(plugin, account);
}

bool PyLoadThriftConnector::login(const std::string& username, const std::string& password) {
    return client->login(username, password);
}

void PyLoadThriftConnector::getUserData(UserData& _return, const std::string& username, const std::string& password) {
    return client->getUserData(_return, username, password);
}

void PyLoadThriftConnector::getAllUserData(std::map<std::string, UserData> & _return) {
    return client->getAllUserData(_return);
}

void PyLoadThriftConnector::getServices(std::map<PluginName, std::map<std::string, std::string> > & _return) {
    return client->getServices(_return);
}

bool PyLoadThriftConnector::hasService(const PluginName& plugin, const std::string& func) {
    return client->hasService(plugin, func);
}

void PyLoadThriftConnector::call(std::string& _return, const ServiceCall& info) {
    return client->call(_return, info);
}

void PyLoadThriftConnector::getAllInfo(std::map<PluginName, std::map<std::string, std::string> > & _return) {
    return client->getAllInfo(_return);
}

void PyLoadThriftConnector::getInfoByPlugin(std::map<std::string, std::string> & _return, const PluginName& plugin) {
    return client->getInfoByPlugin(_return, plugin);
}
