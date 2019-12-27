//
// Created by anarion on 2019/10/22.
//

#ifndef MYWEBSERVER_REQUEST_H
#define MYWEBSERVER_REQUEST_H


#include <sstream>
#include <map>
#include <string>
#include <mutex>
#include <list>
#include <condition_variable>

class Request {
    friend class Listener;
    friend class App;
    friend class Cookie;
protected:
    std::map<std::string, std::string> headers, attributes;
    std::string type, dir, data;
    int cfd;

    static std::mutex requestsMutex;
    static std::list<Request> requestQueue;
    static std::condition_variable requestsCond;
public:
    Request(std::stringstream &&input, int fd);
    Request(Request &&rhs) = default;
    Request(const Request &rhs) = default;
    Request &operator=(const Request &rhs) = default;
    Request &operator=(Request &&rhs) = default;

    const std::string &getDir() const ;
    const std::string &getHeaderVal(const std::string &key) const ;

    static void pushRequest(Request &&request);
    static Request popRequest();
};


#endif //MYWEBSERVER_REQUEST_H
