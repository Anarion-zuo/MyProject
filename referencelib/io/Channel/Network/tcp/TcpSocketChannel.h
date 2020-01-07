//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_TCPSOCKETCHANNEL_H
#define REFERENCELIB_TCPSOCKETCHANNEL_H


#include "../../Channel.h"
#include "../../../../exceptions/system/OpenFdException.h"
#include "../SocketChannel.h"

class TcpSocketChannel : public SocketChannel {
protected:
public:
    TcpSocketChannel() {    // use TCP
        sockfd = (socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
        if (sockfd == -1) {
            throw OpenFdException();
        }
        // for debug
        int ret = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &ret, sizeof(ret));
    }

    explicit TcpSocketChannel(int fd) {
        sockfd = fd;
    }

    TcpSocketChannel(const TcpSocketChannel &rhs) {
        sockfd = rhs.sockfd;
    }

    TcpSocketChannel(TcpSocketChannel &&rhs) noexcept {
        sockfd = rhs.sockfd;
        rhs.sockfd = -1;
    }

    ~TcpSocketChannel() override ;


    bool operator==(const TcpSocketChannel &rhs) const ;

    bool equals(Pointer<Object> rhs) override ;

    bool isValid();

    void connect(const char *host_ip, in_port_t host_port) override ;

    void write(Pointer<Buffer> buffer) override;

    void read(Pointer<Buffer> buffer) override;

    void read(Pointer<SString> str) ;

    size_type write(char *arr, size_type num) override;

    size_type read(char *arr, size_type num) override;
};


#endif //REFERENCELIB_TCPSOCKETCHANNEL_H
