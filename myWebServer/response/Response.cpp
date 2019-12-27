//
// Created by anarion on 2019/10/23.
//

#include <chrono>
#include <sys/socket.h>
#include <zconf.h>
#include <fcntl.h>
#include "Response.h"

std::mutex Response::socketMutex;
std::mutex Response::responsesMutex;
std::condition_variable Response::responsesCond;
std::list<Response> Response::responseQueue;

Response::Response(int code, int fd) : status(code), cfd(fd) {

}

void Response::addHeader(std::string &&key, std::string &&val) {
    headers.insert({std::forward<std::string>(key), std::forward<std::string>(val)});
}

void Response::addHeaderType(std::string &&val) {
    addHeader("Content-Type", std::forward<std::string>(val));
}

void Response::addHeaderLength(size_t length) {
    addHeader("Content-Length", std::to_string(length));
}

void Response::addHeaderLength() {
    addHeaderLength(data.length());
}

void Response::addHeaderDate() {
    time_t now = time(nullptr);
    tm* gmt = gmtime(&now);

    // e.g.: Sat, 22 Aug 2015 11:48:50 GMT
    //       5+   3+4+   5+   9+       3   = 29
    const char* fmt = "%a, %d %b %Y %H:%M:%S GMT";
    char tstr[30];

    strftime(tstr, sizeof(tstr), fmt, gmt);
    addHeader("Date", tstr);
}

void Response::addHeaderContentType(std::string &&val) {
    addHeader("Content-Type", std::forward<std::string>(val));
}

void Response::addHeaderAcceptRanges() {
    addHeader("Accept-Ranges", "bytes");
}

void Response::addHeaderEncoding(std::string &&val) {
    addHeader("Content-Encoding", std::forward<std::string>(val));
}

#include <iostream>
using std::cout, std::endl;

void Response::sendResponse(Response &response) {
    int cfd = response.cfd;
    std::string firstLine = response.status.serialize();

//    std::lock_guard<std::mutex> lock(socketMutex);

    send(cfd, firstLine.c_str(), firstLine.length(), 0);
    response.addHeaderDate();
    int fd = response.ffd;
    // measure file size
    int file_size;
    if (fd != -1) {
        cout << "[response] Measure file size" << endl;
        file_size = lseek(fd, 0, SEEK_END);
        response.addHeaderLength(file_size);
        lseek(fd, 0, SEEK_SET);
        cout << "[response] File size " << file_size << endl;
    } else {
        response.addHeaderLength();
    }
    for (auto &item : response.headers) {
        const std::string &key = item.first, &val = item.second;
        send(cfd, key.c_str(), key.length(), 0);
        send(cfd, ": ", 2, 0);
        send(cfd, val.c_str(), val.length(), 0);
        send(cfd, "\r\n", 2, 0);
    }
    send(cfd, "\r\n", 2, 0);
    if (fd == -1) {
        send(cfd, response.data.c_str(), response.data.length(), 0);
        return;
    }
    char buf[4096];
    while (true) {
        int len = read(fd, buf, 4096);
        if (len <= 0) {
            break;
        }
        send(cfd, buf, 4096, 0);
    }
    cout << "[response] Response sent" << endl;
    close(fd);
}

void Response::pushResponse(Response &&response) {
    std::lock_guard<std::mutex> lock(responsesMutex);
    responseQueue.push_front(std::forward<Response>(response));
    responsesCond.notify_one();
}

Response Response::popResponse() {
    std::unique_lock<std::mutex> lock(responsesMutex);
    responsesCond.wait(lock, []{return !responseQueue.empty();});
    Response response = std::move(responseQueue.back());
    responseQueue.pop_back();
    lock.unlock();
    responsesCond.notify_one();
    return std::move(response);
}
