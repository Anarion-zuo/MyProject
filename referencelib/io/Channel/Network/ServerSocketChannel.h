//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_SERVERSOCKETCHANNEL_H
#define REFERENCELIB_SERVERSOCKETCHANNEL_H


#include <netinet/in.h>
#include "../Channel.h"

class ServerSocketChannel : public Channel {
public:
    virtual void bind(in_port_t port) = 0;
    virtual void listen(int backlog) = 0;
};


#endif //REFERENCELIB_SERVERSOCKETCHANNEL_H
