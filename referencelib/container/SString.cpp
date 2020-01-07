//
// Created by 左钰 on 2019/12/29.
//

#include "SString.h"
#include "../base/Pointer.hpp"
#include "../base/HashFunctions.h"

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

char *SString::cstr() {
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

SString::~SString() {
    delete []begin;
}

bool SString::equals(Pointer<Object> rhs) {
    if (rhs.equals(this)) {
        return true;
    }
    Pointer<SString> p = rhs;
    if (length() != p->length()) {
        return false;
    }
    for (size_type i = 0; i < length(); ++i) {
        if (begin[i] != p->begin[i]) {
            return false;
        }
    }
    return true;
}

hash_type SString::hash() {
    return HashFunctions::global_hashf(begin, length());
}
