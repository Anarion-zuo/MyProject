//
// Created by 左钰 on 2019/12/27.
//

#ifndef MYCPPLIB_REQUEST_H
#define MYCPPLIB_REQUEST_H


#include <Server/Http/RequestType/RequestType.h>
#include <containers/Map/HashMap.hpp>
#include <io/Buffer/Buffer.h>

class Request {
protected:
    RequestType type {};
    SString directory;
    HashMap<SString, SString> headers, params;
    Buffer data;

    Request() = default;

public:
    Request(Request &&rhs) noexcept ;
    static Request readFromBuffer(Buffer &buffer);
};


#endif //MYCPPLIB_REQUEST_H
