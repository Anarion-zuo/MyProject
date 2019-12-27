//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_WRITEFAILEDEXCEPTION_H
#define MYCPPLIB_WRITEFAILEDEXCEPTION_H


#include <exceptions/MyException.hpp>

struct WriteFailedException : public MyException {
    const char *what() const noexcept override {
        return "File writing failed...";
    }
};


#endif //MYCPPLIB_WRITEFAILEDEXCEPTION_H
