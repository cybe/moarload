#ifndef PY_LOAD_THRIFT_CONNECTOR_H
#define PY_LOAD_THRIFT_CONNECTOR_H

#include "py_load_connector.h"
#include "thrift/pyload.h"


class PyLoadThriftConnector : public PyLoadConnector
{
public:
    PyLoadThriftConnector(const std::string& hostname,
                          const unsigned short port);
    virtual ~PyLoadThriftConnector();

    virtual void getConfigValue(std::string& _return, const std::string& category, const std::string& option, const std::string& section);
    virtual void setConfigValue(const std::string& category, const std::string& option, const std::string& value, const std::string& section);
    virtual void getConfig(std::map<std::string, ConfigSection> & _return);
    virtual void getPluginConfig(std::map<std::string, ConfigSection> & _return);
    virtual void pauseServer();
    virtual void unpauseServer();
    virtual bool togglePause();
    virtual void statusServer(ServerStatus& _return);
    virtual int64_t freeSpace();
    virtual void getServerVersion(std::string& _return);
    virtual void kill();
    virtual void restart();
    virtual void getLog(std::vector<std::string> & _return, const int32_t offset);
    virtual bool isTimeDownload();
    virtual bool isTimeReconnect();
    virtual bool toggleReconnect();
    virtual void generatePackages(std::map<std::string, LinkList> & _return, const LinkList& links);
    virtual void checkURLs(std::map<PluginName, LinkList> & _return, const LinkList& urls);
    virtual void parseURLs(std::map<PluginName, LinkList> & _return, const std::string& html, const std::string& url);
    virtual void checkOnlineStatus(OnlineCheck& _return, const LinkList& urls);
    virtual void checkOnlineStatusContainer(OnlineCheck& _return, const LinkList& urls, const std::string& filename, const std::string& data);
    virtual void pollResults(OnlineCheck& _return, const ResultID rid);
    virtual void statusDownloads(std::vector<DownloadInfo> & _return);
    virtual void getPackageData(PackageData& _return, const PackageID pid);
    virtual void getPackageInfo(PackageData& _return, const PackageID pid);
    virtual void getFileData(FileData& _return, const FileID fid);
    virtual void getQueue(std::vector<PackageData> & _return);
    virtual void getCollector(std::vector<PackageData> & _return);
    virtual void getQueueData(std::vector<PackageData> & _return);
    virtual void getCollectorData(std::vector<PackageData> & _return);
    virtual void getPackageOrder(std::map<int16_t, PackageID> & _return, const Destination::type destination);
    virtual void getFileOrder(std::map<int16_t, FileID> & _return, const PackageID pid);
    virtual void generateAndAddPackages(std::vector<PackageID> & _return, const LinkList& links, const Destination::type dest);
    virtual PackageID addPackage(const std::string& name, const LinkList& links, const Destination::type dest);
    virtual void addFiles(const PackageID pid, const LinkList& links);
    virtual void uploadContainer(const std::string& filename, const std::string& data);
    virtual void deleteFiles(const std::vector<FileID> & fids);
    virtual void deletePackages(const std::vector<PackageID> & pids);
    virtual void pushToQueue(const PackageID pid);
    virtual void pullFromQueue(const PackageID pid);
    virtual void restartPackage(const PackageID pid);
    virtual void restartFile(const FileID fid);
    virtual void recheckPackage(const PackageID pid);
    virtual void stopAllDownloads();
    virtual void stopDownloads(const std::vector<FileID> & fids);
    virtual void setPackageName(const PackageID pid, const std::string& name);
    virtual void movePackage(const Destination::type destination, const PackageID pid);
    virtual void moveFiles(const std::vector<FileID> & fids, const PackageID pid);
    virtual void orderPackage(const PackageID pid, const int16_t position);
    virtual void orderFile(const FileID fid, const int16_t position);
    virtual void setPackageData(const PackageID pid, const std::map<std::string, std::string> & data);
    virtual void deleteFinished();
    virtual void restartFailed();
    virtual bool isCaptchaWaiting();
    virtual void getCaptchaTask(CaptchaTask& _return, const bool exclusive);
    virtual void getCaptchaTaskStatus(std::string& _return, const TaskID tid);
    virtual void setCaptchaResult(const TaskID tid, const std::string& result);
    virtual void getEvents(std::vector<EventInfo> & _return, const std::string& uuid);
    virtual void getAccounts(std::vector<AccountInfo> & _return, const bool refresh);
    virtual void getAccountTypes(std::vector<std::string> & _return);
    virtual void updateAccount(const PluginName& plugin, const std::string& account, const std::string& password, const std::map<std::string, std::string> & options);
    virtual void removeAccount(const PluginName& plugin, const std::string& account);
    virtual bool login(const std::string& username, const std::string& password);
    virtual void getUserData(UserData& _return, const std::string& username, const std::string& password);
    virtual void getServices(std::map<PluginName, std::map<std::string, std::string> > & _return);
    virtual bool hasService(const PluginName& plugin, const std::string& func);
    virtual void call(std::string& _return, const ServiceCall& info);
    virtual void getAllInfo(std::map<PluginName, std::map<std::string, std::string> > & _return);
    virtual void getInfoByPlugin(std::map<std::string, std::string> & _return, const PluginName& plugin);

protected:
private:
    PyloadClient* client;
};

#endif // PY_LOAD_THRIFT_CONNECTOR_H
