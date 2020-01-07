//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_RESPONSE_H
#define REFERENCELIB_RESPONSE_H


#include "../../../container/Map/HashMap.hpp"
#include "ResponseStatus.h"
#include "../Cookie/Cookie.h"
#include "../View/resolver/ViewResolver.h"

class Response : public Object {
protected:
    static Pointer<SString> enter;
    HashMap<SString, SString> headers;
    ResponseStatus status {200};
    Cookie cookie;
    Pointer<ViewResolver> viewResolver;

    static void sendEnter(Pointer<TcpSocketChannel> channel);
    static Pointer<SString> contentTypeHtml;
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

    void setViewResolver(Pointer<ViewResolver> vs);

    void setCode(int code);

    void send(Pointer<TcpSocketChannel> channel);
};


#endif //REFERENCELIB_RESPONSE_H
