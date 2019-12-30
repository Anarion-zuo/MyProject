//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_HTTPFORMATEXCEPTION_H
#define REFERENCELIB_HTTPFORMATEXCEPTION_H


#include "../HttpException.h"

struct HttpFormatException : public HttpException {
    const char *what() const noexcept override {
        return "Got a request with false format...";
    }
};


#endif //REFERENCELIB_HTTPFORMATEXCEPTION_H
