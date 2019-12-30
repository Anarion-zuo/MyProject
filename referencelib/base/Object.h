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
typedef unsigned long hash_type;

class SString;

template <typename T>
class Pointer;

class Object {
public:
    Object() = default;
    Object(const Object &) = delete;
    Object(Object &&) noexcept = delete;
    virtual ~Object() = default;

    virtual Pointer<Object> clone();
    virtual bool equals(Pointer<Object> rhs);

    virtual hash_type hash();

    virtual Pointer<SString> toString() ;
};


#endif //REFERENCELIB_OBJECT_H
