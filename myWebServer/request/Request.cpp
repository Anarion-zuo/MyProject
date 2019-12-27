//
// Created by anarion on 2019/10/22.
//

#include "Request.h"

std::mutex Request::requestsMutex;
std::list<Request> Request::requestQueue;
std::condition_variable Request::requestsCond;

Request::Request(std::stringstream &&input, int fd) : cfd(fd) {
    // first line
    std::string str_buf;
    getline(input, str_buf, ' ');  // request type
    type = std::move(str_buf);
    getline(input, str_buf, ' ');  // file directive
    std::stringstream dirs(str_buf);
    getline(input, str_buf, '\r');   // HTTP/1.1
    if (input.get() != '\n') {
        // TODO request format
    }
    // dir & attr
    getline(dirs, dir, '?');
    char c = dirs.get();
    while (c != -1) {
        getline(dirs, str_buf, '=');
        if (str_buf.empty()) {
            break;
        }
        std::string key = std::move(str_buf);
        dirs.get();
        getline(dirs, str_buf, '&');
        std::string val = std::move(str_buf);
        dirs.get();
        attributes[std::move(key)] = std::move(val);
    }
    // headers
    while (true) {
        getline(input, str_buf, ':');
        std::string key = std::move(str_buf);
        if (input.get() != ' ') {
            // TODO request format
        }
        getline(input, str_buf, '\r');
        std::string val = std::move(str_buf);
        headers.insert(std::pair<std::string, std::string>(std::move(key), std::move(val)));
        if (input.get() != '\n') {
            // TODO request format
        }
        if (input.peek() == '\r') {
            input.get();
            break;
        }
    }
    // preserve the rest of buffer as data
    input >> data;
}

const std::string &Request::getDir() const {
    return dir;
}

const std::string &Request::getHeaderVal(const std::string &key) const {
    auto it = headers.find(key);
    if (it == headers.end()) {
        return std::string();
    }
    return it->second;
}

void Request::pushRequest(Request &&request) {
    std::lock_guard<std::mutex> lock(requestsMutex);
    requestQueue.push_front(std::forward<Request>(request));
    requestsCond.notify_one();
}

Request Request::popRequest() {
    std::unique_lock<std::mutex> lock(requestsMutex);
    requestsCond.wait(lock, []{return !requestQueue.empty();});
    Request request = std::move(requestQueue.back());
    requestQueue.pop_back();
    lock.unlock();
    requestsCond.notify_one();
    return std::move(request);
}