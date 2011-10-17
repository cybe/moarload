#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include "../services/pyload_data_store.h"

class PyLoadConnector;

class Request {
public:
    Request(PyloadDataStore& store) : m_store(store) {};
    virtual ~Request() {};
    virtual void execute(PyLoadConnector* pyloadConnection) = 0;
protected:
    PyloadDataStore& m_store;
private:
    // Neither copy nor assign
    Request(const Request&);
    void operator=(const Request&);
};

class GetEventsRequest : public Request {
public:
    GetEventsRequest(PyloadDataStore& store, std::string uuid) : Request(store), m_uuid(uuid) {};
    virtual ~GetEventsRequest() {};
    virtual void execute(PyLoadConnector* pyloadConnection);
private:
    // Neither copy nor assign
    GetEventsRequest(const GetEventsRequest&);
    void operator=(const GetEventsRequest&);
    std::string m_uuid;
};

class GetQueuePackagesRequest : public Request {
public:
    GetQueuePackagesRequest(PyloadDataStore& store) : Request(store) {};
    virtual ~GetQueuePackagesRequest() {};
    virtual void execute(PyLoadConnector* pyloadConnection);
private:
    // Neither copy nor assign
    GetQueuePackagesRequest(const GetQueuePackagesRequest&);
    void operator=(const GetQueuePackagesRequest&);
};

class StatusServerRequest : public Request {
public:
    StatusServerRequest(PyloadDataStore& store) : Request(store) {};
    virtual ~StatusServerRequest() {};
    virtual void execute(PyLoadConnector* pyloadConnection) ;
private:
    // Neither copy nor assign
    StatusServerRequest(const StatusServerRequest&);
    void operator=(const StatusServerRequest&);
};

#endif // REQUEST_H
