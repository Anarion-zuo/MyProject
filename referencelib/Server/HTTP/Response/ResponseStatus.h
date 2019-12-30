//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_RESPONSESTATUS_H
#define REFERENCELIB_RESPONSESTATUS_H


#include "../../../container/Map/HashMap.hpp"
#include "../../../base/Number.hpp"

class ResponseStatus : public Object {
protected:
    static Pointer<HashMap<Int, SString>> map;
    Pointer<Int> code;
public:
    explicit ResponseStatus(int code);
    ~ResponseStatus();

    Pointer<SString> getDescription() const ;
    void set(int n);
    int getCode();
};


#endif //REFERENCELIB_RESPONSESTATUS_H
