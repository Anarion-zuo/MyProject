//
// Created by anarion on 2019/11/27.
//

#ifndef MYCPPLIB_INTEGER_H
#define MYCPPLIB_INTEGER_H

#include "Object.h"

class Integer : public Object {
protected:
    long num;

public:
    Integer() : num(0) {}
    Integer(long n) : num(n) {}

    Integer &operator=(const Integer &rhs) ;
    bool operator==(const Integer &rhs) const ;
    bool operator!=(const Integer &rhs) const ;
    bool operator<(const Integer &rhs) const ;
    bool operator>(const Integer &rhs) const ;
    bool operator<=(const Integer &rhs) const ;
    bool operator>=(const Integer &rhs) const ;
    Integer operator+(const Integer &rhs) const ;
    Integer operator-(const Integer &rhs) const ;
    Integer operator*(const Integer &rhs) const ;
    Integer operator/(const Integer &rhs) const ;
    Integer operator%(const Integer &rhs) const ;
};


#endif //MYCPPLIB_INTEGER_H
