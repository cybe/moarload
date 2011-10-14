#include "pyload_requester.h"

#include "boost/bind.hpp"

#include "../net/py_load_thrift_connector.h"
#include "../net/request.h"
#include "../log.h"

PyloadRequester::PyloadRequester(PyloadDataStore& store) :
    m_store(store),
    m_cs("moarload.ini"),
    m_pyloadConnection(new PyLoadThriftConnector(m_cs.getThriftHostname(),
                                                 m_cs.getThriftPort())),
    m_requestExecutionThread(boost::thread(
                                 boost::bind(&PyloadRequester::executeRequests,
                                             this))) {
    bool loginSuccesfull = m_pyloadConnection->login("buildserver", "buildserver");
    std::string loginMessage("Login to thrift failed");
    if (loginSuccesfull) {
        loginMessage = "Login to thrift succesfull";
    }
    LOG(logINFO) << "Login: " << loginMessage;
}


PyloadRequester::~PyloadRequester() {
    // todo: threads beenden
}

void PyloadRequester::sendRequest(Request* request) {
    m_requestQueue.addRequest(request);
}

void PyloadRequester::executeRequests() {
    while (true) {
        Request* r = m_requestQueue.getNextRequest();
        r->execute(m_pyloadConnection);
        delete r;
    }
}
