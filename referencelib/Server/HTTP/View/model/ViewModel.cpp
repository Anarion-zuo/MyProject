//
// Created by anarion on 2019/12/31.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "ViewModel.h"

ViewModel::ViewModel(Pointer<Map<SString, SString>> map) : map(map) {

}

Pointer<SString> ViewModel::getKey(Pointer<SString> key) {
    return map->get(key);
}
