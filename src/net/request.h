#ifndef REQUEST_H
#define REQUEST_H

class PyLoadConnector;

class Request {
public:
    Request() {};
    virtual ~Request() {};
    virtual void execute(PyLoadConnector* con) = 0;
};

#endif // REQUEST_H