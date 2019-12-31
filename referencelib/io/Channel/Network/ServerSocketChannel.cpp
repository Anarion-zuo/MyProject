//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "ServerSocketChannel.h"
#include "../../../exceptions/system/BindException.h"
#include "../../../exceptions/system/ListenException.h"
#include "../../../exceptions/system/AcceptException.h"
#include "../../../exceptions/system/FcntlException.h"
#include <arpa/inet.h>
#include <fcntl.h>


void ServerSocketChannel::bind(in_port_t host_port) {
    myAddr.sin_port = htons(host_port);
    int ret;
    ret = ::bind(sockfd, reinterpret_cast<sockaddr*>(&myAddr), sizeof(sockaddr_in));
    if (ret == -1) {
        throw BindException();
    }
}

void ServerSocketChannel::listen(int backlog) {
    int ret = ::listen(sockfd, backlog);
    if (ret == -1) {
        throw ListenException();
    }
}

Pointer<SocketChannel> ServerSocketChannel::accept() {
    sockaddr_in addr;
    socklen_t socklen = sizeof(sockaddr_in);
    int cfd = ::accept(sockfd, reinterpret_cast<sockaddr *>(&addr), &socklen);
    if (cfd == -1) {
        throw AcceptException();
    }
    return new SocketChannel(cfd);
}

void ServerSocketChannel::setNonBlock() {
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag == -1) {
        throw FcntlException();
    }
    flag |= O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, flag) == -1) {
        throw FcntlException();
    }
}