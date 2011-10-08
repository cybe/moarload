#include "pyload_data_store.h"

#include "../log.h"
#include "../net/py_load_connector.h"
#include "../net/py_load_thrift_connector.h"

PyloadDataStore::PyloadDataStore()
    : m_cs("moarload.ini")
{
    m_con = new PyLoadThriftConnector(m_cs.getThriftHostname(), m_cs.getThriftPort());
    LOG(logIO) << "-----thrift:";
    m_con = new PyLoadThriftConnector(m_cs.getThriftHostname(), m_cs.getThriftPort());
    bool loginSuccesfull = m_con->login("buildserver", "buildserver");
    LOG(logIO) << "Login: " << loginSuccesfull;
    LOG(logIO) << m_cs.getBackendType();
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
