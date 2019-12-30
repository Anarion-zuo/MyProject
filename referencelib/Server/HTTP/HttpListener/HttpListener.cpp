//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "HttpListener.h"

void HttpListener::run() {
    auto packet = selector->pollPacket();
    Pointer<Request> request = Request::readFromBuffer(packet->buffer);
    packet->buffer.release();
    request->setChannel(packet->channel);
    packet.release();

}
