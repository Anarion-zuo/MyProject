//
// Created by anarion on 2019/10/26.
//

#ifndef MYWEBSERVER_SESSION_H
#define MYWEBSERVER_SESSION_H

#include <iostream>
#include <set>
#include <boost/threadpool/pool.hpp>
#include "../cookie/Cookie.h"
#include <mutex>

class Session {
    typedef size_t sid_t;
private:
    static boost::threadpool::pool timerThreads;
    static std::mutex sessionsLock;
    static void cleanTimeOut();
    sid_t roll();
protected:
    sid_t id;

    static std::map<sid_t, time_t> attrs;

    Session(size_t sid) : id(sid) {}
public:
    static const std::string cookieKey;

    explicit Session(Cookie &cookie);

    bool operator==(const Session &rhs) const;
    bool operator!=(const Session &rhs) const;
    bool operator<(const Session &rhs) const;
    bool operator>(const Session &rhs) const;
    bool operator<=(const Session &rhs) const;
    bool operator>=(const Session &rhs) const;
    bool operator==(size_t id) const;
    bool operator!=(size_t id) const;
    bool operator<(size_t id) const;
    bool operator>(size_t id) const;
    bool operator<=(size_t id) const;
    bool operator>=(size_t id) const;
};


#endif //MYWEBSERVER_SESSION_H
