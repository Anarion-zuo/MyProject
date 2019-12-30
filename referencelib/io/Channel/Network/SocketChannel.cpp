//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "SocketChannel.h"
#include "../../../exceptions/system/ConnectException.h"
#include "../../../exceptions/system/SendException.h"
#include "../../../exceptions/system/ReceiveException.h"
#include "../../../base/Pointer.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include "../../../container/SString.h"

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

void SocketChannel::write(Pointer<Buffer> buffer) {
    buffer->put(sockfd);
}

void SocketChannel::read(Pointer<Buffer> buffer) {
    size_type bufSize = buffer->writtenSize(), ret;
    char *buf = buffer->getArr();
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

void SocketChannel::read(Pointer<SString> str) {
    read(const_cast<char*>(str->cstr()), str->length());
}
