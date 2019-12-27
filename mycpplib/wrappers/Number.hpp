//
// Created by anarion on 2019/12/16.
//

#ifndef MYCPPLIB_NUMBER_HPP
#define MYCPPLIB_NUMBER_HPP

#include <featurers/UseAllocator.h>
#include <featurers/Hashable.h>

template <typename T>
class Number : public UseAllocator, public Hashable {
protected:
    T val;
public:
    Number(T val = 0) : val(val) {}

    template <typename R> Number(const Number<R> &rhs) : val(rhs.val) {}

    template <typename R> Number(Number<R> &&rhs) noexcept : val(rhs.val) {
        rhs.val = 0;
    }

    template <typename R> Number<T> &operator=(const Number<R> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        val = rhs.val;
        return *this;
    }

    template <typename R> Number<T> &operator=(Number<R> &&rhs) noexcept {
        val = rhs.val;
        rhs.val = 0;
        return *this;
    }

    template <typename R> bool operator==(const Number<R> &rhs) const {
        return val == rhs.val;
    }

    template <typename R> bool operator!=(const Number<R> &rhs) const {
        return !(rhs == *this);
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

    hash_type hash() const override {
        return static_cast<hash_type >(val);
    }

    T getNum() const {
        return val;
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


#endif //MYCPPLIB_NUMBER_HPP
