//
// Created by anarion on 2019/12/29.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VECTOR_HPP
#define REFERENCELIB_VECTOR_HPP

#include "../List.h"

template <typename T>
class Vector : public List<T> {
protected:
    T *begin, *end, *cur;
public:
    Vector() : begin(nullptr), end(nullptr), cur(nullptr) {}

    explicit Vector(size_type num) : begin(new T*[num]), cur(begin), end(begin + num) {}
};


#endif //REFERENCELIB_VECTOR_HPP
