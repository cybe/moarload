#include "request_queue.h"

RequestQueue::RequestQueue() {
    //ctor
}

RequestQueue::~RequestQueue() {
    while (!m_requests.empty()) {
        m_requests.pop();
    }
}

void RequestQueue::addRequest(const std::string request) {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_requests.push(request);
    m_cond.notify_all();
}

std::string RequestQueue::getNextRequest() {
    boost::unique_lock<boost::mutex> lock(m_mutex);
    while (m_requests.empty()) {
        m_cond.wait(lock);
    }
    std::string request = m_requests.front();
    m_requests.pop();
    return request;
}
