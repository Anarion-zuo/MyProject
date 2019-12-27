//
// Created by anarion on 2019/11/27.
//

#ifndef MYCPPLIB_DOUBLE_H
#define MYCPPLIB_DOUBLE_H


#include "Object.h"

class Double : public Object {
protected:
    double num;

public:
    Double() : num(0) {}
    Double(double n) : num(n) {}

    Double &operator=(const Double &rhs);
    bool operator==(const Double &rhs);

};


#endif //MYCPPLIB_DOUBLE_H
