#ifndef PYLOAD_DATA_STORE_H
#define PYLOAD_DATA_STORE_H

#include <string>
#include <vector>

#include <boost/thread/shared_mutex.hpp>

#include "../net/thrift/pyload_types.h"

class PyloadDataStore {
private:
    PyloadDataStore(const PyloadDataStore& rhs);
    PyloadDataStore& operator=(const PyloadDataStore& rhs);
    
    boost::shared_mutex m_mutex;

    std::vector<PackageData> m_queuePackages;
    std::vector<EventInfo> m_events;
    
public:
    PyloadDataStore();
    virtual ~PyloadDataStore();

    void setEvents(const std::vector<EventInfo>& events);
    const std::vector<EventInfo> getEvents();
    
    void setQueuePackages(const std::vector<PackageData>& queuePackages);
    const std::vector<PackageData> getQueuePackages();
};

#endif // PYLOAD_DATA_STORE_H
