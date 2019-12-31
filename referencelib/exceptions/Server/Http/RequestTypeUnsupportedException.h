//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_REQUESTTYPEUNSUPPORTEDEXCEPTION_H
#define REFERENCELIB_REQUESTTYPEUNSUPPORTEDEXCEPTION_H


#include "../HttpException.h"

struct RequestTypeUnsupportedException : public HttpException {
    const char *what() const noexcept override {
        return "Having an unknown request type...";
    }
};


#endif //REFERENCELIB_REQUESTTYPEUNSUPPORTEDEXCEPTION_H
