#include "configuration_service.h"

#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


ConfigurationService::ConfigurationService(const std::string& filename) :
    filename(filename)
{
    std::ifstream configfile(filename);
    if (!configfile)
    {
        writeEmptyConfigFile();
    }
    load();
}

ConfigurationService::~ConfigurationService()
{
    save();
}

void ConfigurationService::load()
{
    using boost::property_tree::ptree;
    ptree pt;
    read_ini(filename, pt);
    backendType = pt.get<std::string>("global.backendType", "thrift");
    thriftHostname = pt.get<std::string>("thrift.hostname", "zi0n.homelinux.net");
    thriftPort = pt.get<unsigned short>("thrift.port", 7227);
    httpHostname = pt.get<std::string>("http.hostname", "zi0n.homelinux.net");
    httpPort = pt.get<unsigned short>("http.port", 8081);
}

void ConfigurationService::save()
{
    using boost::property_tree::ptree;
    ptree pt;
    pt.put("global.backendType", backendType);
    pt.put("thrift.hostname", thriftHostname);
    pt.put("thrift.port", thriftPort);
    pt.put("http.hostname", httpHostname);
    pt.put("http.port", httpPort);
    write_ini(filename, pt);
}

void ConfigurationService::writeEmptyConfigFile()
{
    std::fstream f;
    f.open(filename, std::ios::out);
    f << std::endl;
    f.close();
}

std::string ConfigurationService::getBackendType()
{
    return backendType;
}

void ConfigurationService::setBackendType(const std::string& _backendType)
{
    backendType = _backendType;
}

std::string ConfigurationService::getThriftHostname()
{
    return thriftHostname;
}

void ConfigurationService::setThriftHostname(const std::string& _thriftHostname)
{
    thriftHostname = _thriftHostname;
}


unsigned short ConfigurationService::getThriftPort()
{
    return thriftPort;
}


void ConfigurationService::setThriftPort(unsigned short _thriftPort)
{
    thriftPort = _thriftPort;
}


std::string ConfigurationService::getHttpHostname()
{
    return httpHostname;
}


void ConfigurationService::setHttpHostname(const std::string& _httpHostname)
{
    httpHostname = _httpHostname;
}

unsigned short ConfigurationService::getHttpPort()
{
    return httpPort;
}

void ConfigurationService::setHttpPort(unsigned short _httpPort)
{
    httpPort = _httpPort;
}
