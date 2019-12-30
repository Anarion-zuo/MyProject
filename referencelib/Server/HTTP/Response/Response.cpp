//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Response.h"
#include <ctime>
#include <cstdio>

Pointer<SString> Response::enter = new SString("\r\n");

void Response::addHeader(Pointer<SString> key, Pointer<SString> val) {
    headers.put(key, val);
}

void Response::addContentLength(size_type size) {
    Pointer<SString> val = ULong(size).toString();
    addHeader(new SString("Content-Length"), val);
}

void Response::addContentType(Pointer<SString> type) {
    addHeader(new SString("Content-Type"), type);
}

void Response::addDate() {
    char buf[200];
    time_t now = time(nullptr);
    tm tm = *gmtime(&now);
    strftime(buf, 200, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    addHeader(new SString("Date"), SString::copyFromStack(buf));
}

void Response::addServerName(Pointer<SString> name) {
    addHeader(new SString("server"), name);
}

void Response::addStatus() {
    addHeader(new SString("status"), ULong(status.getCode()).toString());
}

void Response::addContentEncoding(Pointer<SString> encoding) {
    addHeader(new SString("Content-Encoding"), encoding);
}

void Response::addCookie() {
    addHeader(new SString("cookie"), cookie.toString());
}

void Response::send(Pointer<SocketChannel> channel) {
    channel->read("HTTP/1.1 ", 9);
    auto c = Int(status.getCode()).toString();
    channel->read(c);
    c.release();
    sendEnter(channel);
    auto it = headers.getBeginIterator();
    while (it->hasNext()) {
        auto en = it->next();
        channel->read(en->getKey());
        channel->read(": ", 2);
        channel->read(en->getVal());
        sendEnter(channel);
    }
    sendEnter(channel);
    it.release();
    // TODO send view
}

void Response::sendEnter(Pointer<SocketChannel> channel) {
    channel->read(const_cast<char*>(enter->cstr()), enter->length());
}
