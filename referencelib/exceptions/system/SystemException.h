//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_SYSTEMEXCEPTION_H
#define REFERENCELIB_SYSTEMEXCEPTION_H


#include "../MyException.h"

struct SystemException : public MyException {
    const char *what() const noexcept override {
        return ::strerror(errno);
    }
};


#endif //REFERENCELIB_SYSTEMEXCEPTION_H
