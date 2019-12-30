//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_NUMBER_HPP
#define REFERENCELIB_NUMBER_HPP

#include "Pointer.hpp"
#include <cstring>
#include <cstdlib>
#include "../container/SString.h"

template <typename T>
class Number : public Object {
protected:
    T val;


    static char *numToStr(int num) {
        char *p = new char [12];
        sprintf(p, "%d", num);
        return p;
    }

    static char *numToStr(unsigned int num) {
        char *p = new char [12];
        sprintf(p, "%u", num);
        return p;
    }

    static char *numToStr(long num) {
        char *p = new char [22];
        sprintf(p, "%l", num);
        return p;
    }

    static char *numToStr(unsigned long num) {
        char *p = new char [22];
        sprintf(p, "%ul", num);
        return p;
    }

    static char *numToStr(float num) {
        char *p = new char [22];
        sprintf(p, "%f", num);
        return p;
    }

    static char *numToStr(double num) {
        char *p = new char [22];
        sprintf(p, "%lf", num);
        return p;
    }

public:
    Number(T val = 0) : val(val) {}

    bool equals(Pointer<Object> rhs) override {
        return val == reinterpret_cast<Number<T>*>(rhs.operator->())->val;
    }

    Pointer<Object> clone() override {
        return new Number(val);
    }

    void setVal(T v) {
        val = v;
    }

    template <typename R> bool operator<(const Number<R> &rhs) const {
        return val < rhs.val;
    }

    template <typename R> bool operator>(const Number<R> &rhs) const {
        return rhs < *this;
    }

    template <typename R> bool operator<=(const Number<R> &rhs) const {
        return !(rhs < *this);
    }

    template <typename R> bool operator>=(const Number<R> &rhs) const {
        return !(*this < rhs);
    }

    template <typename R> auto operator+(const Number<R> &rhs) const -> Number<decltype(rhs.val + val)> {
        return Number(rhs.val + val);
    }

    template <typename R> auto operator-(const Number<R> &rhs) const -> Number<decltype(rhs.val - val)> {
        return Number(rhs.val - val);
    }

    template <typename R> auto operator*(const Number<R> &rhs) const -> Number<decltype(rhs.val * val)> {
        return Number(rhs.val * val);
    }

    template <typename R> auto operator/(const Number<R> &rhs) const -> Number<decltype(rhs.val / val)> {
        return Number(rhs.val / val);
    }

    template <typename R> auto operator%(const Number<R> &rhs) const -> Number<decltype(rhs.val % val)> {
        return Number(rhs.val % val);
    }

    Number<T> &operator++() {
        ++val;
        return *this;
    }

    const Number<T> operator++(int) {
        ++val;
        return *this;
    }

    T getNum() const {
        return val;
    }

    hash_type hash() override {
        return static_cast<hash_type>(val);
    }

    Pointer<SString> toString() override {
        return new SString(numToStr(val));
    }
};

typedef Number<int> Int;
typedef Number<unsigned int> UInt;
typedef Number<short> Short;
typedef Number<unsigned short> UShort;
typedef Number<char> Char;
typedef Number<unsigned char> UChar;
typedef Number<long> Long;
typedef Number<unsigned long> ULong;
typedef Number<float> Float;
typedef Number<double> Double;


#endif //REFERENCELIB_NUMBER_HPP
