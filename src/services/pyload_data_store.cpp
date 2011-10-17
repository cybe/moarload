#include "pyload_data_store.h"

#include <boost/thread/locks.hpp>

#include "../log.h"

PyloadDataStore::PyloadDataStore() {
    //    Bind(wxEVT_NETWORK, &PyloadDataStore::onQueuePackagesUpdated, this, ID_QUEUE_PACKAGES);
    Connect(ID_QUEUE_PACKAGES, wxEVT_NETWORK,
            wxCommandEventHandler(PyloadDataStore::onQueuePackagesUpdated), NULL, this);
}

PyloadDataStore::~PyloadDataStore() {}

void PyloadDataStore::setEvents(const std::vector<EventInfo>& events) {
    boost::unique_lock<boost::shared_mutex> lock(m_mutex);
    m_events = events;
}

const std::vector<EventInfo> PyloadDataStore::getEvents() {
    boost::shared_lock<boost::shared_mutex> lock(m_mutex);
    return m_events;
}

void PyloadDataStore::setQueuePackages(const std::vector<PackageData>& queuePackages) {
    boost::unique_lock<boost::shared_mutex> lock(m_mutex);
    m_queuePackages = queuePackages;
    lock.unlock();
    wxCommandEvent* event = new wxCommandEvent(wxEVT_NETWORK, ID_QUEUE_PACKAGES);
    QueueEvent(event);
}

const std::vector<PackageData> PyloadDataStore::getQueuePackages() {
    boost::shared_lock<boost::shared_mutex> lock(m_mutex);
    return m_queuePackages;
}

void PyloadDataStore::onQueuePackagesUpdated(wxCommandEvent& event) {
    LOG(logDEBUG) << "onQueuePackagesUpdated";
    m_queuePackagesUpdate();
}

const ServerStatus& PyloadDataStore::getServerStatus() {
    boost::shared_lock<boost::shared_mutex> lock(m_mutex);
    return m_serverStatus;
}

void PyloadDataStore::setServerStatus(const ServerStatus& serverStatus) {
    boost::unique_lock<boost::shared_mutex> lock(m_mutex);
    m_serverStatus = serverStatus;
}
