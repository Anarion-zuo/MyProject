//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_HTTPEXCEPTION_H
#define REFERENCELIB_HTTPEXCEPTION_H


#include "../MyException.h"

class HttpException : public MyException {
    const char *what() const noexcept override {
        return "There appears to be an http error...";
    }
};


#endif //REFERENCELIB_HTTPEXCEPTION_H
