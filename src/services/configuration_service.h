#ifndef CONFIGURATION_SERVICE_H
#define CONFIGURATION_SERVICE_H

#include <string>

class ConfigurationService {
public:
    ConfigurationService(const std::string& filename);
    virtual ~ConfigurationService();
    std::string getBackendType() const;
    void setBackendType(const std::string& _backendType);
    std::string getThriftHostname() const;
    void setThriftHostname(const std::string& _thriftHostname);
    unsigned short getThriftPort() const;
    void setThriftPort(unsigned short _thriftPort);
    std::string getHttpHostname() const;
    void setHttpHostname(const std::string& _httpHostname);
    unsigned short getHttpPort() const;
    void setHttpPort(unsigned short _httpPort);
    void load();
    void save();

private:
    std::string filename;
    std::string backendType;
    std::string thriftHostname;
    unsigned short thriftPort;
    std::string httpHostname;
    unsigned short httpPort;

    void writeEmptyConfigFile();
};

#endif // CONFIGURATION_SERVICE_H
