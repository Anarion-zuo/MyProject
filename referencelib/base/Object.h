//
// Created by anarion on 2019/12/28.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_OBJECT_H
#define REFERENCELIB_OBJECT_H

/*
 * The base class for all classes
 */

typedef unsigned long size_type;

class Object {
public:
    Object() = default;
    Object(const Object &) = default;
    Object(Object &&) noexcept = default;

    virtual bool operator==(const Object &rhs) const;
    virtual Object *clone();
};


#endif //REFERENCELIB_OBJECT_H
