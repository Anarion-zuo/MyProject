//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_MTCPCHANNEL_H
#define REFERENCELIB_MTCPCHANNEL_H


#include "../tcp/TcpSocketChannel.h"

class MtcpChannel : public SocketChannel {
protected:
    struct segment {
        int seq, ack;
        int flags;
        /*
         * 000...00 SYN ACK FIN
         */

        bool isSyn();
        bool isAck();
        bool isFin();
        void setSyn();
        void setAck();
        void setFin();
        void clrSyn();
        void clrAck();
        void clrFin();

        char *data;
        int data_len;

        segment() = default;
        explicit segment(char *p);
        ~segment();
    };

    void sendSegment(segment *seg, sockaddr *cliaddr, socklen_t clilen);
    segment *recvSegment();

    static int rwnd;
public:
    MtcpChannel();

    void connect(const char *host_ip, in_port_t host_port) override;

    void write(Pointer<Buffer> buffer) override ;

};


#endif //REFERENCELIB_MTCPCHANNEL_H
