//
// Created by 左钰 on 2019/12/27.
//

#include <containers/List/SString.h>
#include <exceptions/Server/Http/HttpFormatException.h>
#include "Request.h"

Request Request::readFromBuffer(Buffer &buffer) {
    Request request;
    size_type len;

    // request type
    char *str = buffer.getUntil('\r', &len);
    char *dst = strchr(str, ' ');
    *dst = 0;
    request.type = RequestType::makeType(str);

    // request directory
    char *p = dst + 1;
    dst = strchr(p, ' ');
    char dir[dst - p + 2];
    strcpy(dir, p);
    Allocator::deallocate(str, len);

    // parse request directory
    p = strchr(dir, '?');
    *p = 0;
    request.directory = dir;
    ++p;

    // parse request parameters

    // parse headers
    str = buffer.getUntil('\n', nullptr);
    if (str) {
        throw HttpFormatException();
    }

}

Request::Request(Request &&rhs) noexcept : type(rhs.type), headers(std::move(rhs.headers)), params(std::move(rhs.params)), data(std::move(rhs.data)){

}
