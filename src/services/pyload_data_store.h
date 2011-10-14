#ifndef PYLOAD_DATA_STORE_H
#define PYLOAD_DATA_STORE_H

#include <string>
#include <vector>

#include "../services/configuration_service.h"
#include "../net/thrift/pyload_types.h"
#include "../net/request_queue.h"

class PyLoadConnector;

class PyloadDataStore {
private:
    PyloadDataStore(const PyloadDataStore& rhs);
    PyloadDataStore& operator=(const PyloadDataStore& rhs);

    PyLoadConnector* m_con;
    ConfigurationService m_cs;
    std::vector<PackageData> m_queuePackages;
    
    RequestQueue m_requestQueue;
    std::vector<EventInfo> m_events;
    
public:
    PyloadDataStore();
    virtual ~PyloadDataStore();
    void updateQueuePackageData();

    std::vector<PackageData>& getQueuePackages() {
        return m_queuePackages;
    }
    
    void requestEvents(std::string uuid);
    void setEvents(std::vector<EventInfo>& events);
    std::vector<EventInfo> getEvents();
};

#endif // PYLOAD_DATA_STORE_H
