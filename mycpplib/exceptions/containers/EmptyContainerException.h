//
// Created by anarion on 2019/12/1.
//

#ifndef MYCPPLIB_EMPTYCONTAINEREXCEPTION_H
#define MYCPPLIB_EMPTYCONTAINEREXCEPTION_H


#include <exceptions/MyException.hpp>

struct EmptyContainerException : public MyException {
    const char *what() const noexcept {
        return "Empty container, nothing to give.";
    }
};


#endif //MYCPPLIB_EMPTYCONTAINEREXCEPTION_H
