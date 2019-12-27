//
// Created by anarion on 2019/10/23.
//

#ifndef MYWEBSERVER_RESPONSE_H
#define MYWEBSERVER_RESPONSE_H


#include <string>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../status/Status.h"
#include <list>

class Response {
    friend class PageApp;
    friend class ImgApp;
protected:
    std::map<std::string, std::string> headers;
    Status status;
    std::string data;
    int cfd;

    static std::mutex socketMutex;

    static std::mutex responsesMutex;
    int ffd = -1;

    static std::condition_variable responsesCond;
    static std::list<Response> responseQueue;
public:
    explicit Response(int code, int fd);

    void addHeader(std::string &&key, std::string &&val);
    void addHeaderType(std::string &&val);
    void addHeaderLength();
    void addHeaderLength(size_t length);
    void addHeaderDate();
    void addHeaderContentType(std::string &&val);
    void addHeaderAcceptRanges();
    void addHeaderEncoding(std::string &&val);

    void setCode(int code) {
        status.setCode(code);
    }

    void setFFd(int fd) {
        ffd = fd;
    }

    static void sendResponse(Response &response);


    static Response popResponse();
    static void pushResponse(Response &&response);

};


#endif //MYWEBSERVER_RESPONSE_H
