//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "MtcpServerChannel.h"
#include "../../../../exceptions/system/BindException.h"

void MtcpServerChannel::bind(in_port_t port) {
    int ret = ::bind(sockfd, reinterpret_cast<sockaddr*>(&myAddr), sizeof(myAddr));
    if (ret < 0) {
        throw BindException();
    }
}

void MtcpServerChannel::listen(int backlog) {

}

MtcpServerChannel::MtcpServerChannel(in_port_t port) : MtcpChannel() {
    memset(&myAddr, 0, sizeof(sockaddr_in));
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myAddr.sin_port = htons(port);
}
