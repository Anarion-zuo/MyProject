//
// Created by anarion on 2019/11/7.
//

#ifndef MYSTL_BINARY_FUNCTOR_HPP
#define MYSTL_BINARY_FUNCTOR_HPP

#include "functor.hpp"

template <class Ret, class Arg1, class Arg2>
struct binary_functor {
    typedef unsigned long size_type;
    virtual Ret operator()(const Arg1 &, const Arg1 &) = 0;
};

template<class Obj>
struct less_functor : public binary_functor<bool, Obj, Obj> {
    bool operator()(const Obj &arg1, const Obj &arg2) {
        return arg1 < arg2;
    }
};

template <class Obj>
struct larger_functor : public binary_functor<bool, Obj, Obj> {
    bool operator()(const Obj &arg1, const Obj &arg2) {
        return arg1 > arg2;
    }
};

template <typename Obj>
struct equal_functor : public binary_functor<bool, Obj, Obj> {
    bool operator()(const Obj &arg1, const Obj &arg2) {
        return arg1 == arg2;
    }
};

#endif //MYSTL_BINARY_FUNCTOR_HPP
