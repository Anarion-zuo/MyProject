//
// Created by anarion on 2019/11/10.
//

#ifndef MYSTL_STRING_HPP
#define MYSTL_STRING_HPP

#include <cstring>
#include <allocator/Allocator.hpp>
#include <new>
#include <cstdio>
#include <base-classes/Object.h>

class SString : public Object {
protected:
    typedef unsigned long size_type;

    struct StringNode {
        char *data;
        size_type length;
        StringNode *next;

        StringNode(const char *s, size_type length, StringNode *next = nullptr) : data(Allocator::allocate<char>(length)), length(length), next(next) {
            memcpy(data, s, length);
            data[length] = 0;
        }

        StringNode(const char *s, StringNode *next = nullptr) : length(strlen(s)), next(next) {
            data = Allocator::allocate<char>(length);
            memcpy(data, s, length);
            data[length] = 0;
        }

        StringNode(const StringNode &rhs) : data(Allocator::allocate<char>(rhs.length)), length(rhs.length), next(nullptr) {
            memcpy(data, rhs.data, length);
            data[length] = 0;
        }

        StringNode(StringNode &&rhs) noexcept : data(rhs.data), length(rhs.length), next(nullptr) {
            rhs.data = nullptr;
            rhs.length = 0;
        }

        ~StringNode() {
            Allocator::deallocate(data, length);
        }

        static void deleteList(StringNode *node);
        StringNode *clone();
    };

    StringNode *head = nullptr, *end = nullptr;
    size_type length = 0;

    void bundle();

    size_type KMP(char *str1, size_type len1, char *str2, size_type len2);
public:
    SString() {}
    SString(const char *str, size_type length) : length(length) {
        if (!str || !length) {
            return;
        }
        head = Allocator::allocate<StringNode>();
        ::new (head) StringNode(str, length);
        end = head;
    }
    SString(const char *str) : length(strlen(str)) {
        if (!str || !length) {
            return;
        }
        head = Allocator::allocate<StringNode>();
        ::new (head) StringNode(str, length);
        end = head;
    }
    SString(void *p) {
        head = Allocator::allocate<StringNode>();
        char buf[14];
        sprintf(buf, "%p", p);
        ::new (head) StringNode(buf);
    }
    SString(unsigned int num) {
        head = Allocator::allocate<StringNode>();
        char buf[10];
        sprintf(buf, "%u", num);
        ::new (head) StringNode(buf);
    }
    SString(int num) {
        head = Allocator::allocate<StringNode>();
        char buf[11];
        sprintf(buf, "%d", num);
        ::new (head) StringNode(buf);
    }
    SString(unsigned long num) {
        head = Allocator::allocate<StringNode>();
        char buf[19];
        sprintf(buf, "%lu", num);
        ::new (head) StringNode(buf);
    }
    SString(long num) {
        head = Allocator::allocate<StringNode>();
        char buf[11];
        sprintf(buf, "%ld", num);
        ::new (head) StringNode(buf);
    }
    SString(float num) {
        head = Allocator::allocate<StringNode>();
        char buf[35];
        sprintf(buf, "%f", num);
        ::new (head) StringNode(buf);
    }
    SString(double num) {
        head = Allocator::allocate<StringNode>();
        char buf[35];
        sprintf(buf, "%lf", num);
        ::new (head) StringNode(buf);
    }
    ~SString() {
        StringNode::deleteList(head);
    }
    void clear();
    SString(SString &rhs) : length(rhs.length) {
        rhs.bundle();
        if (!rhs.length) {
            return;
        }
        head = Allocator::allocate<StringNode>();
        ::new (head) StringNode(*rhs.head);
        end = head;
    }
    SString(SString &&rhs) noexcept : head(rhs.head), length(rhs.length), end(rhs.end) {
        rhs.length = 0;
        rhs.head = nullptr;
        rhs.end = nullptr;
    }
    SString &operator=(SString &rhs) {
        if (&rhs == this) {
            return *this;
        }
        rhs.bundle();
        StringNode::deleteList(head);
        if (!rhs.length) {
            head = nullptr;
            end = nullptr;
            length = 0;
            return *this;
        }
        head = Allocator::allocate<StringNode>();
        ::new (head) StringNode(*rhs.head);
        length = rhs.length;
        end = head;
        return *this;
    }
    SString &operator=(SString &&rhs) noexcept {
        if (&rhs == this) {
            return *this;
        }
        StringNode::deleteList(head);
        head = rhs.head;
        length = rhs.length;
        rhs.length = 0;
        rhs.head = nullptr;
        end = rhs.end;
        rhs.end = nullptr;
        return *this;
    }

    const char *c_str();

    bool isEmpty();
    size_type size();

    void append(SString &&rhs);

    SString &operator+=(SString &&rhs);
    SString &operator+=(SString &rhs);
    SString operator+(SString &rhs);

    char operator[](size_type index);

    void print();
};


#endif //MYSTL_STRING_HPP
