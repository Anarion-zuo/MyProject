//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_VIEWMODEL_H
#define REFERENCELIB_VIEWMODEL_H


#include "../../../../container/Map.hpp"

class ViewModel {
protected:
    Pointer<Map<SString, SString>> map;
public:
    explicit ViewModel(Pointer<Map<SString, SString>> map);

    Pointer<SString> getKey(Pointer<SString> key);
};


#endif //REFERENCELIB_VIEWMODEL_H
