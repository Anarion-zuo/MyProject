//
// Created by anarion on 2019/12/1.
//

#ifndef MYCPPLIB_MEMORYALLOCATIONEXCEPTION_H
#define MYCPPLIB_MEMORYALLOCATIONEXCEPTION_H


#include <exceptions/MyException.hpp>

struct MemoryAllocationException : public MyException{
    const char *what() const noexcept {
        return "No extra memory.";
    }
};


#endif //MYCPPLIB_MEMORYALLOCATIONEXCEPTION_H
