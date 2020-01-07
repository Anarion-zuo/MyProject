//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Request.h"
#include "../../../exceptions/Server/Http/HttpFormatException.h"
#include <cstdio>

Pointer<Request> Request::readFromBuffer(Pointer<Buffer> buffer) {
    Pointer<Request> request = new Request;
    size_type len;
    int ret;
    buffer->flip();   // switch to reading mode

    // first line

    // request type
    char *type = buffer->getUntil(' ', &len);
    request->type = RequestType::makeType(type);
    delete [] type;

    // request directory
    buffer->get();
    Pointer<Buffer> dirparam = buffer->getUntil(' ');
    dirparam->flip();
    Pointer<Buffer> dirbuf = dirparam->getUntil('?');
    if (dirparam->unReadSize() == 0) {
        // no paramters
    } else {   // parse parameters
        dirparam->get();
        if (dirparam->unReadSize()) {
            while (true) {
                char *key = dirparam->getUntil('=', &len);
                dirparam->get();
                char *val = dirparam->getUntil('&', &len);
                request->params.put(new SString(key), new SString(val));
                if (dirparam->unReadSize() == 0) {
                    break;
                }
                dirparam->get();
            }
        }
    }
    request->directory = SString::copyFromStack(dirbuf->getArr());
    dirparam.release();

    // HTTP version
    buffer->get();
    Pointer<Buffer> versionBuffer = buffer->getUntil('\r');

    // headers
    buffer->get();
    char c = buffer->get();
    if (c != '\n') {
        throw HttpFormatException();
    }
    // a line
    while (true) {
        Pointer<Buffer> line = buffer->getUntil('\r');
        if (line->writtenSize() == 0) {
            line.release();
            break;
        }
        line->flip();
        char *key = line->getUntil(':', &len);
        line->get();
        c = line->get();
        if (c != ' ') {
            throw HttpFormatException();
        }
        request->headers.put(new SString(key), new SString(line->getRest()));
        line.release();
        buffer->get();
        c = buffer->get();
        if (c != '\n') {
            throw HttpFormatException();
        }
    }

    // data
    buffer->get();
    c = buffer->get();
    if (c != '\n') {
        throw HttpFormatException();
    }
    buffer->put(request->data);
    return request;
}

void Request::print() {
    printf("Request directory: ");
    printf("%s\n", directory->cstr());
    printf("Request parameters:\n");
    Pointer<SString> paramsStr = params.toString();
    printf("%s", paramsStr->cstr());
    paramsStr.release();
    printf("\nRequest headers:\n");
    Pointer<SString> headersStr = headers.toString();
    printf("%s\n", headersStr->cstr());
    headersStr.release();

}

void Request::setChannel(Pointer<TcpSocketChannel> ch) {
    channel = ch;
}

RequestType Request::getType() const {
    return type;
}

Pointer<TcpSocketChannel> Request::getChannel() {
    return channel;
}

Pointer<SString> Request::getDirectory() {
    return directory;
}

Pointer<SString> Request::getHeader(Pointer<SString> key) {
    return headers.get(key);
}

Pointer<SString> Request::getParam(Pointer<SString> key) {
    return params.get(key);
}
