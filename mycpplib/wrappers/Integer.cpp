//
// Created by anarion on 2019/11/27.
//

#include "Integer.h"

bool Integer::operator==(const Integer &rhs) const {
    return rhs.num == num;
}

Integer &Integer::operator=(const Integer &rhs) {
    num = rhs.num;
    return *this;
}

bool Integer::operator!=(const Integer &rhs) const {
    return rhs.num != num;
}

bool Integer::operator<(const Integer &rhs) const {
    return num < rhs.num;
}

bool Integer::operator>(const Integer &rhs) const {
    return num > rhs.num;
}

bool Integer::operator<=(const Integer &rhs) const {
    return num <= rhs.num;
}

bool Integer::operator>=(const Integer &rhs) const {
    return num >= rhs.num;
}

Integer Integer::operator+(const Integer &rhs) const {
    return num + rhs.num;
}

Integer Integer::operator-(const Integer &rhs) const {
    return num - rhs.num;
}

Integer Integer::operator*(const Integer &rhs) const {
    return num * rhs.num;
}

Integer Integer::operator/(const Integer &rhs) const {
    return num / rhs.num;
}

Integer Integer::operator%(const Integer &rhs) const {
    return num % rhs.num;
}
