//
// Created by anarion on 2019/10/22.
//

#ifndef MYWEBSERVER_LISTENER_H
#define MYWEBSERVER_LISTENER_H

#include <boost/threadpool.hpp>
#include <string>
#include "../request/Request.h"
#include "../response/Response.h"
#include <mutex>
#include <list>
#include <condition_variable>

struct sockaddr_in;
class Listener {
private:
    explicit Listener(int port_num = 9898, int back_log = 1024, int max_conn = 1024);
    ~Listener();
    static Listener *instance;
    int portNum, lfd, backlog, maxConnNum, epfd;
    static boost::threadpool::pool threadPool;

    static void registerApps();



    static void readPipe(int fd);
    static void dispatch();
    static void sendBack();
public:
    static const Listener &getInstance();
    static void startListening(int port_num, int back_log, int max_conn);

    Listener(const Listener &) = delete;
    Listener &operator=(const Listener &) = delete;
    Listener(Listener &&) = delete;
    Listener &operator=(Listener &&) = delete;

};


#endif //MYWEBSERVER_LISTENER_H
