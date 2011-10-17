#ifndef PYLOAD_DATA_STORE_H
#define PYLOAD_DATA_STORE_H

#define wxEVT_NETWORK 10040
#define ID_QUEUE_PACKAGES 1000

#include <string>
#include <vector>

#include <boost/thread/shared_mutex.hpp>
#ifdef Yield
    #undef Yield
#endif
#include <wx/event.h>

#include "../lib/signals/signal.h"
#include "../net/thrift/pyload_types.h"

class PyloadDataStore : public wxEvtHandler {
private:
    PyloadDataStore(const PyloadDataStore& rhs);
    PyloadDataStore& operator=(const PyloadDataStore& rhs);

    void onQueuePackagesUpdated(wxCommandEvent& event);

    Signals::Signal0<void> m_queuePackagesUpdate;
    boost::shared_mutex m_mutex;
    std::vector<PackageData> m_queuePackages;
    std::vector<EventInfo> m_events;
    ServerStatus m_serverStatus;

public:
    PyloadDataStore();
    virtual ~PyloadDataStore();

    void setEvents(const std::vector<EventInfo>& events);
    const std::vector<EventInfo> getEvents();

    void setQueuePackages(const std::vector<PackageData>& queuePackages);
    const std::vector<PackageData> getQueuePackages();
    Signals::Signal0<void>& getQueuePackagesUpdate() {
        return m_queuePackagesUpdate;
    }
    
    void setServerStatus(const ServerStatus& serverStatus);
    const ServerStatus& getServerStatus();
};

#endif // PYLOAD_DATA_STORE_H
