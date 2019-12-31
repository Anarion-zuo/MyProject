//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_CHANNEL_H
#define REFERENCELIB_CHANNEL_H


#include "../../base/Object.h"
#include "../Buffer/Buffer.h"

class Channel : public Object {
protected:
    static const size_type blockSize = 4096;

public:
    virtual ~Channel() = default;

    virtual void write(Pointer<Buffer> buffer) = 0;
    virtual void read(Pointer<Buffer> buffer) = 0;
    virtual size_type write(char *arr, size_type num) = 0;
    virtual size_type read(char *arr, size_type num) = 0;
    virtual void transferTo(Channel &channel);
    virtual void transferFrom(Channel &channel);
};


#endif //REFERENCELIB_CHANNEL_H
