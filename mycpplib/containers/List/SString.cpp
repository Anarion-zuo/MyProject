//
// Created by anarion on 2019/11/28.
//

#include <utility>
#include "SString.h"

void SString::StringNode::deleteList(SString::StringNode *node) {
    while (node) {
        StringNode *next = node->next;
        Allocator::deallocate(node);
        node = next;
    }
}

SString::StringNode *SString::StringNode::clone() {
    StringNode *head = Allocator::allocate<StringNode>(), *node = this, *res = head;
    ::new (head) StringNode(*node);
    node = node->next;
    while (node) {
        head->next = Allocator::allocate<StringNode>();
        head = head->next;
        ::new (head) StringNode(*node);
        node = node->next;
    }
    return res;
}

void SString::bundle() {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        return;
    }
    char *newspace = Allocator::allocate<char>(length), *p = newspace;
    StringNode *node = head;
    while (node) {
        memcpy(p, node->data, node->length);
        p += node->length;
        node = node->next;
    }
    StringNode::deleteList(head);
    head = Allocator::allocate<StringNode>();
    ::new (head) StringNode(newspace, length);
}

const char *SString::c_str() {
    bundle();
    return head->data;
}

SString SString::operator+(SString &rhs) {
    SString lhs(*this);
    lhs += SString(rhs);
    return std::move(lhs);
}

void SString::append(SString &&rhs) {
    if (!rhs.length) {
        return;
    }
    if (!length) {
        operator=(std::forward<SString>(rhs));
        return;
    }
    end->next = rhs.head;
    end = rhs.end;
    length += rhs.length;
    rhs.length = 0;
    rhs.head = nullptr;
    rhs.end = nullptr;
}

bool SString::isEmpty() {
    return !length;
}

SString::size_type SString::size() {
    return length;
}

SString &SString::operator+=(SString &&rhs) {
    append(std::forward<SString>(rhs));
    return *this;
}

SString &SString::operator+=(SString &rhs) {
    append(SString(rhs));
    return *this;
}

char SString::operator[](SString::size_type index) {
    StringNode *node = head;
    if (index >= length) {
        return 0;
    }
    while (index >= node->length) {
        index -= node->length;
    }
    return node->data[index];
}

void SString::print() {
    StringNode *node = head;
    while (node) {
        printf("%.*s", (int)node->length, node->data);
        node = node->next;
    }
}

void SString::clear() {
    StringNode::deleteList(head);
    head = nullptr;
    end = nullptr;
    length = 0;
}

size_type SString::KMP(char *str1, size_type len1, char *str2, size_type len2) {
    size_type nextArr[len1];
    // next arr

}
