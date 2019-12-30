//
// Created by anarion on 2019/12/28.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "Object.h"
#include "Pointer.hpp"
#include "../container/SString.h"
#include <cstdio>


Pointer<Object> Object::clone() {
    Object *p = new Object();
    return p;
}

bool Object::equals(Pointer<Object> rhs) {
    return rhs.operator->() == this;
}

hash_type Object::hash() {
    return reinterpret_cast<hash_type>(this);
}

Pointer<SString> Object::toString() {
    char *str = new char[22];
    sprintf(str, "Object@%p", this);
    return new SString(str);
}
