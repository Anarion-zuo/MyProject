//
// Created by 左钰 on 2019/12/10.
//

#ifndef MYCPPLIB_INVALIDOPERATIONEXCEPTION_H
#define MYCPPLIB_INVALIDOPERATIONEXCEPTION_H


#include <exceptions/MyException.hpp>

class InvalidOperationException : public MyException {
public:
    const char *what() const noexcept {
        return "The container does not support such operation.";
    }
};


#endif //MYCPPLIB_INVALIDOPERATIONEXCEPTION_H
