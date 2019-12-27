//
// Created by 左钰 on 2019/12/15.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exceptions/io/Network/ConnectException.h>
#include <exceptions/io/Network/ReceiveException.h>
#include <exceptions/io/Network/SendException.h>
#include <exceptions/io/Network/SocketCloseException.h>
#include "SocketChannel.h"

SocketChannel::~SocketChannel() {
    int ret;
    ret = ::close(sockfd);
    if (ret == -1) {
        perror("Socket close:");
    }
}

void SocketChannel::connect(const char *host_ip, in_port_t host_port) {
    sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_addr.s_addr = inet_addr(host_ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host_port);
    int ret;
    ret = ::connect(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in));
    if (ret == -1) {
        throw ConnectException();
    }
}

void SocketChannel::write(Buffer &buffer) {
    buffer.put(sockfd);
}

void SocketChannel::read(Buffer &buffer) {
    size_type bufSize = buffer.writtenSize(), ret;
    char *buf = buffer.getArr();
    read(buf, bufSize);
}

size_type SocketChannel::write(char *arr, size_type num) {
    int ret;
    ret = ::recv(sockfd, arr, num, 0);
    if (ret == -1) {
        throw SendException();
    }
    return ret;
}

size_type SocketChannel::read(char *arr, size_type num) {
    int ret;
    ret = ::send(sockfd, arr, num, 0);
    if (ret == -1) {
        throw ReceiveException();
    }
    return ret;
}

bool SocketChannel::isValid() {
    return sockfd > 0;
}

bool SocketChannel::operator==(const SocketChannel &rhs) const {
    return sockfd == rhs.sockfd;
}

int SocketChannel::getSocketFd() const {
    return sockfd;
}

