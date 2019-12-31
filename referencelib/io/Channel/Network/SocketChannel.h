//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_SOCKETCHANNEL_H
#define REFERENCELIB_SOCKETCHANNEL_H


#include "../Channel.h"
#include "../../../exceptions/system/OpenFdException.h"
#include <netinet/in.h>

class SocketChannel : public Channel {
protected:
    int sockfd;
public:
    SocketChannel()
            : sockfd(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) {    // use TCP
        if(sockfd == -1) {
            throw OpenFdException();
        }
    }

    explicit SocketChannel(int fd)
            : sockfd(fd) {}

    SocketChannel(const SocketChannel &rhs) : sockfd(rhs.sockfd) {}

    SocketChannel(SocketChannel &&rhs) noexcept
            : sockfd(rhs.sockfd) {
        rhs.sockfd = -1;
    }

    ~SocketChannel() override ;

    int getSocketFd() const ;

    bool operator==(const SocketChannel &rhs) const ;

    bool isValid();

    void connect(const char *host_ip, in_port_t host_port);

    void write(Pointer<Buffer> buffer) override;

    void read(Pointer<Buffer> buffer) override;

    void read(Pointer<SString> str) ;

    size_type write(char *arr, size_type num) override;

    size_type read(char *arr, size_type num) override;
};


#endif //REFERENCELIB_SOCKETCHANNEL_H
