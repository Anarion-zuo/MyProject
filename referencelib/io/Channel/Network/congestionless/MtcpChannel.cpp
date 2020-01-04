//
// Created by anarion on 2020/1/3.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "MtcpChannel.h"
#include "../../../Buffer/Buffer.h"
#include "../../../../exceptions/container/IndexOutOfRangeException.h"
#include <sys/socket.h>

MtcpChannel::MtcpChannel() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);   // use UDP
    if (sockfd < 0) {
        throw OpenFdException();
    }
}

void MtcpChannel::write(Pointer<Buffer> buffer) {

}

void MtcpChannel::sendSegment(segment *seg, sockaddr *cliaddr, socklen_t clilen) {
    char *p = reinterpret_cast<char*>(seg);
    int len = sizeof(segment);
    char sending[len + seg->data_len];
    memcpy(sending, p, len);
    memcpy(sending + len, seg->data, seg->data_len);
    ::sendto(sockfd, sending, (len + seg->data_len), 0, cliaddr, clilen);
}

MtcpChannel::segment *MtcpChannel::recvSegment() {
    Buffer buffer(1024);
    buffer.put(sockfd);
    segment *seg = new segment(buffer.getArr());
    return seg;
}

void MtcpChannel::connect(const char *host_ip, in_port_t host_port) {

}

bool MtcpChannel::segment::isSyn() {
    return 0b100 & flags;
}

bool MtcpChannel::segment::isAck() {
    return 0b10 & flags;
}

bool MtcpChannel::segment::isFin() {
    return 0b1 & flags;
}

void MtcpChannel::segment::setSyn() {
    flags |= 0b100;
}

void MtcpChannel::segment::setAck() {
    flags |= 0b10;
}

void MtcpChannel::segment::setFin() {
    flags |= 0b1;
}

void MtcpChannel::segment::clrSyn() {
    flags &= ~0b100;
}

void MtcpChannel::segment::clrAck() {
    flags &= ~0b10;
}

void MtcpChannel::segment::clrFin() {
    flags &= ~0b1;
}

MtcpChannel::segment::segment(char *p) {
    segment *ps = reinterpret_cast<segment*>(p);
    seq = ps->seq;
    ack = ps->ack;
    data_len = ps->data_len;
    data = new char[data_len];
    memcpy(data, reinterpret_cast<char*>(ps) + sizeof(segment), data_len);
}

MtcpChannel::segment::~segment() {
    delete []data;
}
