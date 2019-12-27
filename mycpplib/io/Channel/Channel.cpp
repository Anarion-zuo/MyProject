//
// Created by 左钰 on 2019/12/14.
//

#include "Channel.h"
#include <unistd.h>

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
