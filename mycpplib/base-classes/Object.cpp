//
// Created by anarion on 2019/11/27.
//

#include "Object.h"
#include <ctime>
#include <cstdlib>
#include <functors/unary_functor.h>
#include <typeinfo>
#include <containers/List/SString.h>
#include <utility>

SString Object::toString() const {
    SString res("Obj@");
    res += SString((void *)this);
    return std::move(res);
}
