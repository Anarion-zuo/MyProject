//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_SOCKETCHANNEL_H
#define REFERENCELIB_SOCKETCHANNEL_H


#include "../Channel.h"
#include <netinet/in.h>

class SocketChannel : public Channel {
protected:
    int sockfd;
public:
    int getSocketFd() const ;
    virtual void connect(const char *host_ip, in_port_t host_port) = 0;
};



#endif //REFERENCELIB_SOCKETCHANNEL_H
