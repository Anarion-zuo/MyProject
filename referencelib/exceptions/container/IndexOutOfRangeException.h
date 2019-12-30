//
// Created by 左钰 on 2019/12/30.
//

#ifndef REFERENCELIB_INDEXOUTOFRANGEEXCEPTION_H
#define REFERENCELIB_INDEXOUTOFRANGEEXCEPTION_H


#include "../MyException.h"

struct IndexOutOfRangeException : public MyException {
    const char *what() const noexcept override {
        return "Index out of range when trying to index a container.";
    }
};


#endif //REFERENCELIB_INDEXOUTOFRANGEEXCEPTION_H
