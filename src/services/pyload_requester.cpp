#include "pyload_requester.h"

#include <boost/thread/thread.hpp>

#include "../net/py_load_thrift_connector.h"
#include "request.h"
#include "../log.h"


// RequestWorker

RequestWorker::RequestWorker(RequestQueue& requestQueue,
                             const std::string hostname,
                             const unsigned short port) :
    m_hostname(hostname),
    m_port(port),
    m_requestQueue(requestQueue),
    m_pyloadConnection(NULL) {
}

RequestWorker::~RequestWorker() {
    delete m_pyloadConnection;
}

void RequestWorker::run() {
    try {
        Logger::setPidName("net");
        LOG(logDEBUG) << "request execution thread started";
        m_pyloadConnection = new PyLoadThriftConnector(m_hostname,
                                                       m_port);
        bool loginSuccesfull = m_pyloadConnection->login("buildserver", "buildserver");
        std::string loginMessage("Login to thrift failed");
        if (loginSuccesfull) {
            loginMessage = "Login to thrift succesfull";
        }
        LOG(logINFO) << loginMessage;

        while (true) {
            Request* r = m_requestQueue.getNextRequest();
            r->execute(m_pyloadConnection);
            delete r;
        }
    } catch (boost::thread_interrupted&) {
        LOG(logDEBUG) << "received thread interruption signal";
    }
}


// RecurringRequestsWorker

RecurringRequestsWorker::RecurringRequestsWorker(RequestQueue& requestQueue,
                                                 PyloadDataStore& dataStore) :
    m_requestQueue(requestQueue),
    m_dataStore(dataStore) {
}

void RecurringRequestsWorker::run() {
    try {
        Logger::setPidName("loop");
        LOG(logDEBUG) << "recurring requests thread started";
        while (true) {
            m_requestQueue.addRequest(new GetEventsRequest(m_dataStore, "pyload-uuid"));
            m_requestQueue.addRequest(new StatusServerRequest(m_dataStore));
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
    } catch (boost::thread_interrupted&) {
        LOG(logDEBUG) << "received thread interruption signal";
    }
}


// PyloadRequester

PyloadRequester::PyloadRequester(PyloadDataStore& dataStore) :
    m_cs("moarload.ini"),
    m_dataStore(dataStore),
    m_requestWorker(m_requestQueue,
                    m_cs.getThriftHostname(),
                    m_cs.getThriftPort()),
    m_recurringRequestsWorker(m_requestQueue, m_dataStore) {
    LOG(logDEBUG) << "starting request execution thread";
    m_requestExecutionThread = boost::thread(&RequestWorker::run, &m_requestWorker);
    LOG(logDEBUG) << "starting recurring requests execution thread";
    m_recurringRequestsExecutionThread = boost::thread(&RecurringRequestsWorker::run, &m_recurringRequestsWorker);
}

PyloadRequester::~PyloadRequester() {
    LOG(logDEBUG) << "stopping recurring requests execution thread";
    m_recurringRequestsExecutionThread.interrupt();
    m_recurringRequestsExecutionThread.join();
    LOG(logDEBUG) << "stopping request execution thread";
    m_requestExecutionThread.interrupt();
    m_requestExecutionThread.join();
}

void PyloadRequester::sendRequest(Request* request) {
    m_requestQueue.addRequest(request);
}
