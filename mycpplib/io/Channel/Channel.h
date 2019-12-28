//
// Created by 左钰 on 2019/12/14.
//

#ifndef MYCPPLIB_CHANNEL_H
#define MYCPPLIB_CHANNEL_H


#include <featurers/UnCopiable.h>
#include <io/Buffer/Buffer.h>
#include <utility>

class Channel : public Hashable {
protected:
    static const size_type blockSize = 4096;

public:
    virtual ~Channel() = default;

    virtual void write(Buffer &buffer) = 0;
    virtual void read(Buffer &buffer) = 0;
    virtual size_type write(char *arr, size_type num) = 0;
    virtual size_type read(char *arr, size_type num) = 0;
    virtual void transferTo(Channel &channel);
    virtual void transferFrom(Channel &channel);
};


#endif //MYCPPLIB_CHANNEL_H
