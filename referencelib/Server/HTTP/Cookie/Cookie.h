//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_COOKIE_H
#define REFERENCELIB_COOKIE_H


#include "../../../base/Object.h"
#include "../../../container/Map/HashMap.hpp"
#include "../../../io/Channel/Network/tcp/TcpSocketChannel.h"

class Cookie : public Object {
protected:
    HashMap<SString, SString> map;
public:
    void add(Pointer<SString> key, Pointer<SString> val);
    void send(Pointer<TcpSocketChannel> channel);
};


#endif //REFERENCELIB_COOKIE_H
