//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_REQUEST_H
#define REFERENCELIB_REQUEST_H


#include "../../../base/Object.h"
#include "../../../io/Buffer/Buffer.h"
#include "RequestType.h"
#include "../../../container/SString.h"
#include "../../../container/Map/HashMap.hpp"
#include "../../../io/Channel/Network/tcp/TcpSocketChannel.h"

class Request : public Object {
protected:
    RequestType type {};
    Pointer<SString> directory;
    HashMap<SString, SString> headers, params;
    Buffer data {1024};
    Pointer<TcpSocketChannel> channel;

public:
    static Pointer<Request> readFromBuffer(Pointer<Buffer> buffer);
    void print();
    void setChannel(Pointer<TcpSocketChannel> ch);
    RequestType getType() const ;
    Pointer<TcpSocketChannel> getChannel();
    Pointer<SString> getDirectory();

    Pointer<SString> getHeader(Pointer<SString> key);
    Pointer<SString> getParam(Pointer<SString> key);
};


#endif //REFERENCELIB_REQUEST_H
