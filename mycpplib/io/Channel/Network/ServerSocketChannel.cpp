//
// Created by 左钰 on 2019/12/15.
//

#include <arpa/inet.h>
#include "ServerSocketChannel.h"
#include <fcntl.h>
#include <exceptions/io/Network/ListenException.h>
#include <exceptions/io/Network/BindException.h>

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

SocketChannel ServerSocketChannel::accept() {
    sockaddr_in addr;
    socklen_t socklen = sizeof(sockaddr_in);
    int cfd = ::accept(sockfd, reinterpret_cast<sockaddr *>(&addr), &socklen);
    if (cfd == -1) {
        throw SocketCreateException();
    }
    connectedHosts.put(Number<int>(cfd));
    return SocketChannel(cfd);
}

void ServerSocketChannel::setNonBlock() {
    int flag = fcntl(sockfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flag);
}

