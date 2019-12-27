//
// Created by anarion on 2019/12/16.
//

#ifndef MYCPPLIB_SYSTEMEXCEPTION_H
#define MYCPPLIB_SYSTEMEXCEPTION_H


#include <exceptions/MyException.hpp>

struct SystemException : public MyException {
    const char *what() const noexcept override {
        return ::strerror(errno);
    }
};


#endif //MYCPPLIB_SYSTEMEXCEPTION_H
