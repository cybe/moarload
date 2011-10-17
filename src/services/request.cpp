#include "request.h"

#include <vector>

#include "../log.h"
#include "../net/py_load_connector.h"
#include "../net/thrift/pyload_types.h"

void GetEventsRequest::execute(PyLoadConnector* pyloadConnection) {
    LOG(logDEBUG) << "GetEventsRequest";
    std::vector<EventInfo> events;
    pyloadConnection->getEvents(events, m_uuid);
    m_store.setEvents(events);
}

void GetQueuePackagesRequest::execute(PyLoadConnector* pyloadConnection) {
    LOG(logDEBUG) << "GetQueuePackagesRequest";
    std::vector<PackageData> data;
    pyloadConnection->getQueueData(data);
    m_store.setQueuePackages(data);
}

void StatusServerRequest::execute(PyLoadConnector* pyloadConnection)
{
    LOG(logDEBUG) << "StatusServerRequest";
    ServerStatus status;
    pyloadConnection->statusServer(status);
}
