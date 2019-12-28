//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef MYCPPLIB_HTTPFORMATEXCEPTION_H
#define MYCPPLIB_HTTPFORMATEXCEPTION_H


#include <exceptions/MyException.hpp>

struct HttpFormatException : public MyException {
    const char *what() const noexcept override {
        return "Received HTTP package holds wrong format.";
    }
};


#endif //MYCPPLIB_HTTPFORMATEXCEPTION_H
