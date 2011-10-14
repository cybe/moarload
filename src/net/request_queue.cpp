#include "request_queue.h"

#include "request.h"

RequestQueue::RequestQueue() {
    //ctor
}

RequestQueue::~RequestQueue() {
    while (!m_requests.empty()) {
        m_requests.pop();
    }
}

void RequestQueue::addRequest(Request* request) {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    request->execute(NULL);
    m_requests.push(request);
    m_cond.notify_all();
}

Request* RequestQueue::getNextRequest() {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    while (m_requests.empty()) {
        m_cond.wait(lock);
    }
    Request* request = m_requests.front();
    m_requests.pop();
    return request;
}
