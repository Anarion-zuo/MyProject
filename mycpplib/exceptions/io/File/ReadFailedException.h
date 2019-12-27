//
// Created by 左钰 on 2019/12/15.
//

#ifndef MYCPPLIB_READFAILEDEXCEPTION_H
#define MYCPPLIB_READFAILEDEXCEPTION_H


#include <exceptions/MyException.hpp>

struct ReadFailedException : public MyException {
    const char *what() const noexcept {
        return "File reading failed...";
    }
};


#endif //MYCPPLIB_READFAILEDEXCEPTION_H
