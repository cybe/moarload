#include "pyload_data_store.h"

#include "../log.h"
#include "../net/py_load_connector.h"
#include "../net/py_load_thrift_connector.h"
#include "../net/request.h"
#include "../net/request_queue.h"

PyloadDataStore::PyloadDataStore() :
    m_cs("moarload.ini") {
    LOG(logIO) << "-----thrift:";
    m_con = new PyLoadThriftConnector(m_cs.getThriftHostname(), m_cs.getThriftPort());
    bool loginSuccesfull = m_con->login("buildserver", "buildserver");
    LOG(logIO) << "Login: " << loginSuccesfull;
    std::string version;
    m_con->getServerVersion(version);
    LOG(logIO) << "version: " << version;
    
}

PyloadDataStore::~PyloadDataStore() {
    delete m_con;
}

void PyloadDataStore::updateQueuePackageData() {
    m_con->getQueueData(m_queuePackages);
}

void PyloadDataStore::requestEvents(std::string uuid) {
    m_requestQueue.addRequest(new GetEventsRequest(*this, uuid));
}

void PyloadDataStore::setEvents(std::vector<EventInfo>& events) {
    m_events = events;
}

std::vector<EventInfo> PyloadDataStore::getEvents() {
    return m_events;
}
