#include "pyload_requester.h"

#include "../net/py_load_thrift_connector.h"
#include "../net/request.h"
#include "../log.h"

RequestWorker::RequestWorker(RequestQueue& requestQueue,
                             const std::string& hostname,
                             const unsigned short port) :
    m_requestQueue(requestQueue),
    m_hostname(hostname),
    m_port(port),
    m_pyloadConnection(NULL) {
}

RequestWorker::~RequestWorker() {
    delete m_pyloadConnection;
}

void RequestWorker::run() {
    m_pyloadConnection = new PyLoadThriftConnector(m_hostname,
                                                   m_port);
    bool loginSuccesfull = m_pyloadConnection->login("buildserver", "buildserver");
    std::string loginMessage("Login to thrift failed");
    if (loginSuccesfull) {
        loginMessage = "Login to thrift succesfull";
    }
    LOG(logINFO) << loginMessage;

    //    while (true) {
    //        Request* r = m_requestQueue.getNextRequest();
    //        r->execute(m_pyloadConnection);
    //        delete r;
    //    }
}

PyloadRequester::PyloadRequester(PyloadDataStore& store) :
    m_store(store),
    m_cs("moarload.ini"),
    m_requestWorker(m_requestQueue,
                    m_cs.getThriftHostname(),
                    m_cs.getThriftPort()) {
    //m_requestExecutionThread(&RequestWorker::run, &m_requestWorker) {
}


PyloadRequester::~PyloadRequester() {
    // todo: threads beenden
}

void PyloadRequester::sendRequest(Request* request) {
    m_requestQueue.addRequest(request);
}

void PyloadRequester::startThread() {
    LOG(logDEBUG) << "starting worker thread";
    m_requestExecutionThread = boost::thread(&RequestWorker::run, &m_requestWorker);
}
