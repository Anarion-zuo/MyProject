//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_MTCPSERVERCHANNEL_H
#define REFERENCELIB_MTCPSERVERCHANNEL_H

#include "../ServerSocketChannel.h"
#include "MtcpChannel.h"

class MtcpServerChannel : public ServerSocketChannel, public MtcpChannel {
protected:
    sockaddr_in myAddr;
public:
    explicit MtcpServerChannel(in_port_t port);

    void bind(in_port_t port) override;

    void listen(int backlog) override;
};


#endif //REFERENCELIB_MTCPSERVERCHANNEL_H
