//
// Created by anarion on 2019/12/1.
//

#ifndef MYCPPLIB_INDEXOUTOFRANGEEXCEPTION_H
#define MYCPPLIB_INDEXOUTOFRANGEEXCEPTION_H


#include <exceptions/MyException.hpp>

class IndexOutOfRangeException : public MyException {
public:
    const char *what() const noexcept {
        return "Index out of Range. Try limiting the input of [] or method get.";
    }
};


#endif //MYCPPLIB_INDEXOUTOFRANGEEXCEPTION_H
