#ifndef PYLOAD_REQUESTER_H
#define PYLOAD_REQUESTER_H

#include <boost/thread.hpp>

#include "pyload_data_store.h"
#include "configuration_service.h"
#include "../net/request_queue.h"


class PyLoadConnector;
class Request;

class PyloadRequester {
public:
    PyloadRequester(PyloadDataStore& store);
    virtual ~PyloadRequester();

    void sendRequest(Request* request);

private:
    // Neither copy nor assign
    PyloadRequester(const PyloadRequester&);
    void operator=(const PyloadRequester&);
    void executeRequests();

    PyloadDataStore& m_store;
    ConfigurationService m_cs;
    RequestQueue m_requestQueue;
    PyLoadConnector* m_pyloadConnection;
    boost::thread m_requestExecutionThread;
};

#endif // PYLOAD_REQUESTER_H
