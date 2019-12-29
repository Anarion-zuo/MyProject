//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_SSTRING_H
#define REFERENCELIB_SSTRING_H


#include "../base/Object.h"
#include <cstring>


class SString : public Object {
protected:
    char *begin = nullptr, *end = nullptr, *cur = nullptr;

    void expand(size_type oldsize);

public:
    SString() = default;
    explicit SString(char *str);  // should be only used when str is upon heap

    size_type length() const ;
    size_type capacity() const ;
    char get(size_type index);
    void append(const char *str);
    void append(const char *str, size_type len);
    void append(Pointer<SString> rhs);
    const char *cstr() const ;
};


#endif //REFERENCELIB_SSTRING_H
