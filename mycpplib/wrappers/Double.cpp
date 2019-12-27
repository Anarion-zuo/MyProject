//
// Created by anarion on 2019/11/27.
//

#include "Double.h"

Double &Double::operator=(const Double &rhs) {
    num = rhs.num;
    return *this;
}

bool Double::operator==(const Double &rhs) {
    return num == rhs.num;
}
