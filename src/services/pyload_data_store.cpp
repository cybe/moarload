#include "pyload_data_store.h"

#include "../log.h"
#include "../net/py_load_connector.h"
#include "../net/py_load_thrift_connector.h"

PyloadDataStore::PyloadDataStore()
    : m_cs("moarload.ini")
{
    LOG(logIO) << "-----thrift:";
    m_con = new PyLoadThriftConnector(m_cs.getThriftHostname(), m_cs.getThriftPort());
    bool loginSuccesfull = m_con->login("buildserver", "buildserver");
    LOG(logIO) << "Login: " << loginSuccesfull;
    std::string version;
    m_con->getServerVersion(version);
    LOG(logIO) << "version: " << version;
}

PyloadDataStore::~PyloadDataStore()
{
    delete m_con;
}

void PyloadDataStore::updateQueuePackageData()
{
    m_con->getQueueData(m_queuePackages);
}
