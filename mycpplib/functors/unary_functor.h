//
// Created by anarion on 2019/11/7.
//

#ifndef MYSTL_UNARY_FUNCTOR_H
#define MYSTL_UNARY_FUNCTOR_H

#include "functor.hpp"

template <class Ret, class Arg>
class unary_functor {
    virtual Ret operator() (Arg arg) = 0;
};


#endif //MYSTL_UNARY_FUNCTOR_H
