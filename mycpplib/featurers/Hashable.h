//
// Created by anarion on 2019/12/16.
//

#ifndef MYCPPLIB_HASHABLE_H
#define MYCPPLIB_HASHABLE_H

#include <base-classes/Object.h>
#include <cstdlib>
#include <ctime>
#include <functors/unary_functor.h>

typedef unsigned long hash_type;


namespace HashFuncs
{
    typedef hash_type (*hf_t)(const char *ptr, size_type len);

    static hash_type BKDRHash(const char *ptr, size_type len) {
        hash_type res = 0;
        for (unsigned long i = 0; i < len; ++i) {
            res = (res << 7) + (res << 1) + res + ptr[i];
        }
        return res;
    }

    static hash_type SDBMHash(const char *ptr, size_type len) {
        hash_type res = 0;
        for (unsigned long i = 0; i < len; ++i) {
            res = (res << 6) + (res << 16) - res + ptr[i];
        }
        return res;
    }

    static hash_type APHash(const char *ptr, size_type len) {
        hash_type res = 0;
        for (unsigned long i = 0; i < len; ++i) {
            if (i & 1) {
                res ^= (~((res << 11) ^ ptr[i] ^ (res >> 5)));
            } else {
                res ^= ((res << 7) ^ ptr[i] ^ (res >> 3));
            }
        }
        return res & 0x7FFFFFFF;
    }

    static hash_type FNVHash(const char *ptr, size_type len) {
        if (!*ptr) {
            return 0;
        }
        hash_type res = 0;
        for (unsigned long i = 0; i < len; ++i) {
            res *= 16777619;
            res ^= ptr[i];
        }
        return res;
    }

    static hash_type MySQLHash(const char *ptr, size_type len) {
        unsigned int nr = 1, nr2 = 4;
        hash_type res = 0;
        for (unsigned long i = 0; i < len; ++i) {
            nr ^= (((nr & 63) + nr2) * ((unsigned int)ptr[i])) + (nr << 8);
            nr2 += 3;
        }
        return nr;
    }

    static hash_type (*getHashF())(const char *ptr, size_type len) {
        hf_t hfs[] = {BKDRHash, SDBMHash, APHash, FNVHash, MySQLHash};
        unsigned int len = sizeof(hfs) >> 3;
        srand((unsigned int)time(nullptr));
        unsigned int index = rand() % len;
        return hfs[index];
    }

    static hf_t global_hashf = getHashF();

} // namespace HashFuncs

template <typename T>
struct GlobalHash : public unary_functor<hash_type, const T &> {
    hash_type operator()(const T &obj) override {
        return HashFuncs::global_hashf(reinterpret_cast<const char *>(&obj), sizeof(T));
    }
};

template <>
struct GlobalHash<int> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<unsigned int> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<short> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<unsigned short> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<long> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<unsigned long> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<char> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};

template <>
struct GlobalHash<unsigned char> : public unary_functor<hash_type, const int &> {
    hash_type operator()(const int &obj) override {
        return obj;
    }
};


struct Hashable {
    virtual hash_type hash() const {
        return reinterpret_cast<hash_type>(this);
    }
};


#endif //MYCPPLIB_HASHABLE_H
