//
// Created by 左钰 on 2019/12/29.
//

#include "SString.h"
#include "../base/Pointer.hpp"

size_type SString::length() const {
    return cur - begin;
}

char SString::get(size_type index) {
    return begin[index];
}

void SString::append(const char *str) {
    size_type len = strlen(str);
    append(str, len);
}

SString::SString(char *str) : begin(str) {
    cur = str + strlen(str);
    end = cur;
}

void SString::expand(size_type oldsize) {
    if (!begin) {
        begin = new char[oldsize << 1ul];
        cur = begin;
        end = begin + (oldsize << 1ul);
        *cur = 0;
        return;
    }
    size_type newsize = oldsize << 1ul, curoff = length();
    char *newspace = new char[newsize], *oldspace = begin;
    begin = newspace;
    cur = curoff + begin;
    end = newsize + begin;
    memcpy(newspace, oldspace, oldsize);
    delete[] oldspace;
}

size_type SString::capacity() const {
    return end - begin;
}

void SString::append(const char *str, size_type len) {
    size_type requiredsize = len + length();
    if (capacity() <= requiredsize) {
        expand(requiredsize);
    }
    memcpy(cur, str, len);
    cur += len;
    *cur = 0;
}

void SString::append(Pointer<SString> rhs) {
    append(rhs->begin, rhs->length());
}

const char *SString::cstr() const {
    return begin;
}

Pointer<SString> SString::copyFromStack(char *str) {
    size_type len = strlen(str);
    char *p = new char[len + 1];
    strcpy(p, str);
    return new SString(p);
}

Pointer<SString> SString::toString() {
    return (clone().operator->());
}

Pointer<Object> SString::clone() {
    return copyFromStack(begin).operator->();
}
