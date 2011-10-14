#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <queue>
#include <string>

#include <boost/thread.hpp>

class RequestQueue {
public:
    RequestQueue();
    virtual ~RequestQueue();

    void addRequest(const std::string request);
    std::string getNextRequest();

private:
    // Neither copy nor assign
    RequestQueue(const RequestQueue&);
    void operator=(const RequestQueue&);

    boost::mutex m_mutex;
    boost::condition_variable_any m_cond;
    std::queue<std::string> m_requests;
};

#endif // REQUEST_QUEUE_H