//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Channel.h"

void Channel::transferTo(Channel &channel) {
    if (&channel == this) {
        return;
    }
    char buf[blockSize];
    size_type len = 0;
    while((len = write(buf, blockSize)) >= 0) {
        channel.read(buf, len);
    }
}

void Channel::transferFrom(Channel &channel) {
    channel.transferTo(*this);
}
