#include "request.h"

#include <vector>

#include "py_load_connector.h"
#include "thrift/pyload_types.h"

void GetEventsRequest::execute(PyLoadConnector* con) {
    std::vector<EventInfo> events;
    con->getEvents(events, m_uuid);
    m_store.setEvents(events);
}
