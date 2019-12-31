//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_RESPONSE_H
#define REFERENCELIB_RESPONSE_H


#include "../../../container/Map/HashMap.hpp"
#include "ResponseStatus.h"
#include "../Cookie/Cookie.h"

class Response : public Object {
protected:
    static Pointer<SString> enter;
    HashMap<SString, SString> headers;
    ResponseStatus status {200};
    Cookie cookie;

    static void sendEnter(Pointer<SocketChannel> channel);
public:
    // headers
    void addHeader(Pointer<SString> key, Pointer<SString> val);
    void addContentLength(size_type size);
    void addContentType(Pointer<SString> type);
    void addDate();
    void addServerName(Pointer<SString> name);
    void addStatus();
    void addContentEncoding(Pointer<SString> encoding);
    void addCookie();

    void send(Pointer<SocketChannel> channel);
};


#endif //REFERENCELIB_RESPONSE_H
