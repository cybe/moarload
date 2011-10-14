#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include "../services/pyload_data_store.h"

class PyLoadConnector;

class Request {
public:
    Request(PyloadDataStore& store) : m_store(store) {};
    virtual ~Request() {};
    virtual void execute(PyLoadConnector* con) = 0;

protected:
    PyloadDataStore& m_store;
};

class GetEventsRequest : public Request {
public:
    GetEventsRequest(PyloadDataStore& store, std::string uuid) : Request::Request(store), m_uuid(uuid) {};
    virtual ~GetEventsRequest() {};
    virtual void execute(PyLoadConnector* con);

private:
    GetEventsRequest(const GetEventsRequest&);
    void operator=(const GetEventsRequest&);
    std::string m_uuid;
};

#endif // REQUEST_H
