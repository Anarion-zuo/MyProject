//
// Created by 左钰 on 2019/12/30.
//

#ifndef REFERENCELIB_MYEXCEPTION_H
#define REFERENCELIB_MYEXCEPTION_H


#include <exception>

struct MyException : public std::exception {
    const char *what() const noexcept override {
        return "There has been an exception...";
    }
};


#endif //REFERENCELIB_MYEXCEPTION_H
