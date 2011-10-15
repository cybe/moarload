#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <queue>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

class Request;

class RequestQueue {
public:
    RequestQueue();
    virtual ~RequestQueue();

    void addRequest(Request* request);
    Request* getNextRequest();

private:
    // Neither copy nor assign
    RequestQueue(const RequestQueue&);
    void operator=(const RequestQueue&);

    boost::mutex m_mutex;
    boost::condition_variable_any m_cond;
    std::queue<Request*> m_requests;
};

#endif // REQUEST_QUEUE_H