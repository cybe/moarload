#include "pyload_data_store.h"

#include <boost/thread/locks.hpp>

#include "../log.h"

PyloadDataStore::PyloadDataStore() {}

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
}

const std::vector<PackageData> PyloadDataStore::getQueuePackages() {
    boost::shared_lock<boost::shared_mutex> lock(m_mutex);
    return m_queuePackages;
}
