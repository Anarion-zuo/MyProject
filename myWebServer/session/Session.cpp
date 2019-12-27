//
// Created by anarion on 2019/10/26.
//

#include "Session.h"
#include <random>
#include <ctime>

std::map<Session::sid_t, time_t> Session::attrs;
boost::threadpool::pool timerThreads(1024);
std::mutex Session::sessionsLock;
const std::string Session::cookieKey = "SESSION";

Session::Session(Cookie &cookie) {
    sid_t sid = cookie.getSessionId();
    if (sid == 0) {
        id = roll();
    } else {
        auto it = attrs.find(sid);
        if (it == attrs.end()) {
            id = roll();
        } else {
            id = sid;
        }
    }
    std::unique_lock<std::mutex> lock(sessionsLock);
    lock.lock();
    time_t now = time(nullptr);
    attrs[id] = now;
    lock.unlock();
    cookie.add(cookieKey, std::to_string(id));
}

bool Session::operator==(const Session &rhs) const {
    return id == rhs.id;
}

bool Session::operator!=(const Session &rhs) const {
    return id != rhs.id;
}

bool Session::operator<(const Session &rhs) const {
    return id < rhs.id;
}

bool Session::operator>(const Session &rhs) const {
    return rhs < *this;
}

bool Session::operator<=(const Session &rhs) const {
    return !(rhs < *this);
}

bool Session::operator>=(const Session &rhs) const {
    return !(*this < rhs);
}

bool Session::operator==(size_t id) const {
    return this->id == id;
}

bool Session::operator>=(size_t id) const {
    return this->id >= id;
}

bool Session::operator<=(size_t id) const {
    return this->id <= id;
}

bool Session::operator<(size_t id) const {
    return this->id < id;
}

bool Session::operator>(size_t id) const {
    return this->id > id;
}

bool Session::operator!=(size_t id) const {
    return this->id != id;
}

Session::sid_t Session::roll() {
    std::default_random_engine e;
    sid_t ret;
    while ((ret = e()) != 0);
    return ret;
}

void Session::cleanTimeOut() {
    for (auto it = attrs.begin(); it != attrs.end();) {
        time_t now = time(nullptr);
        if (now - it->second > 1800) {
            std::unique_lock<std::mutex> lock(sessionsLock);
            lock.lock();
            attrs.erase(it++);
            lock.unlock();
        } else {
            ++it;
        }
    }
}

