#ifndef PYLOAD_REQUESTER_H
#define PYLOAD_REQUESTER_H

#include <boost/thread.hpp>

#include "pyload_data_store.h"
#include "configuration_service.h"
#include "request_queue.h"


class PyLoadConnector;
class Request;

class RequestWorker {
public:
    RequestWorker(RequestQueue& requestQueue,
                  const std::string hostname,
                  const unsigned short port);
    virtual ~RequestWorker();
    void run();

private:
    // Neither copy nor assign
    RequestWorker(const RequestWorker&);
    void operator=(const RequestWorker&);
    const std::string m_hostname;
    const unsigned short m_port;
    RequestQueue& m_requestQueue;
    PyLoadConnector* m_pyloadConnection;
};


class RecurringRequestsWorker {
public:
    RecurringRequestsWorker(RequestQueue& requestQueue, PyloadDataStore& m_dataStore);
    virtual ~RecurringRequestsWorker() {};
    void run();
    
private:
    // Neither copy nor assign
    RecurringRequestsWorker(const RecurringRequestsWorker&);
    void operator=(const RecurringRequestsWorker&);
    
    RequestQueue& m_requestQueue;
    PyloadDataStore& m_dataStore;
};


class PyloadRequester {
public:
    PyloadRequester(PyloadDataStore& dataStore);
    virtual ~PyloadRequester();
    void sendRequest(Request* request);

private:
    // Neither copy nor assign
    PyloadRequester(const PyloadRequester&);
    void operator=(const PyloadRequester&);

    ConfigurationService m_cs;
    PyloadDataStore& m_dataStore;
    RequestQueue m_requestQueue;
    RequestWorker m_requestWorker;
    RecurringRequestsWorker m_recurringRequestsWorker;
    boost::thread m_requestExecutionThread;
    boost::thread m_recurringRequestsExecutionThread;
};

#endif // PYLOAD_REQUESTER_H
