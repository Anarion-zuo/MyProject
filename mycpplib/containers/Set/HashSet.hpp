//
// Created by anarion on 2019/11/24.
//

#ifndef MYSTL_HASHTABLE_HPP
#define MYSTL_HASHTABLE_HPP

#include "allocator/Allocator.hpp"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <functors/unary_functor.h>
#include <base-classes/Object.h>
#include <utility>
#include "Set.hpp"

typedef unsigned long HashCode;


template <typename Obj>
class HashSet : public Set<Obj> {
protected:
    typedef unsigned long size_type;
    struct HashNode {
        HashNode *next;
        hash_type hcode;
        Obj *ptr;

        HashNode(const Obj &obj, HashNode *next, hash_type hc) : next(next), hcode(hc), ptr(Allocator::allocate<Obj>()) {
            ::new (ptr) Obj(obj);
        }

        HashNode(Obj &&obj, HashNode *next, hash_type hc) : next(next), hcode(hc), ptr(Allocator::allocate<Obj>()) {
            ::new (ptr) Obj(std::forward<Obj>(obj));
        }

        ~HashNode() {
            Allocator::deallocate(ptr);
        }

    };

    HashNode **heads = Allocator::allocate<HashNode*>(20);
    size_type count = 0, headerSize = 20;

    void expand() {
        size_type newsize = headerSize << 1;
        HashNode **newheads = Allocator::allocate<HashNode*>(newsize);
        memset(newheads, 0, newsize);
        for (size_type i = 0; i < headerSize; ++i) {
            HashNode *node = heads[i];
            while (node) {
                size_type index = node->hcode % newsize;
                HashNode *next = node->next;
                node->next = newheads[index];
                newheads[index] = node;
                node = node->next;
            }
        }
        Allocator::deallocate(heads, headerSize);
        heads = newheads;
        headerSize = newsize;
    }

    static HashNode *probeLinkedList(HashNode *head, hash_type code) {
        while (head) {
            if (head->hcode == code) {
                return head;
            }
            head = head->next;
        }
        return nullptr;
    }

    HashNode *getNode(const Obj &obj) {
        hash_type code = obj.hash();
        size_type index = (code % headerSize);
        HashNode *node = probeLinkedList(heads[index], code);
        if (!node) {
            return nullptr;
        }
        if (obj == *node->ptr) {
            return node;
        }
        return nullptr;
    }

    void insertOne(const Obj &obj) {
        auto p = Allocator::allocate<HashNode>();
        hash_type code = obj.hash();
        ::new (p) HashNode(obj, nullptr, code);
        size_type index = (code % headerSize);
        HashNode *head = heads[index], *pre = nullptr;
        while (head) {
            if (head->hcode == code) {
                break;
            }
            pre = head;
            head = head->next;
        }
        if (head) {
            p->next = head->next;
            Allocator::deallocate(head);
            pre->next = p;
        } else if (pre) {
            pre->next = p;
            ++count;
        }
        else {
            heads[index] = p;
            ++count;
        }
    }

    void insertOne(Obj &&obj) {
        auto p = Allocator::allocate<HashNode>();
        hash_type code = obj.hash();
        ::new (p) HashNode(std::forward<Obj>(obj), nullptr, code);
        size_type index = (code % headerSize);
        HashNode *head = heads[index], *pre = nullptr;
        while (head) {
            if (head->hcode == code) {
                break;
            }
            pre = head;
            head = head->next;
        }
        if (head) {
            p->next = head->next;
            Allocator::deallocate(head);
            if (pre)
                pre->next = p;
            else
                heads[index] = p;
        } else if (pre) {
            pre->next = p;
            ++count;
        }
        else {
            heads[index] = p;
            ++count;
        }
    }

    // regardless of order
    HashNode *cloneLinkedList(HashNode *src) {
        if (!src) {
            return nullptr;
        }
        HashNode *sn = src, *dn,
        *head = Allocator::allocate<HashNode>();
        ::new (head) HashNode(*sn->ptr, nullptr, sn->hcode);
        sn = sn->next;
        while (sn) {
            // clone node
            dn = Allocator::allocate<HashNode>();
            ::new (dn) HashNode(*sn->ptr, nullptr, sn->hcode);
            dn->next = head;
            head = dn;
            sn = sn->next;
        }
        return head;
    }

public:
    class iterator : public Set<Obj>::iterator {
    protected:
        HashNode **headerAddr;
        HashNode *node;

    public:
        iterator(HashNode **hi, HashNode *n, size_type count) : Set<Obj>::iterator(count, 0), headerAddr(hi), node(n) {}

        Obj &next() override {
            while (node == nullptr) {
                ++headerAddr;
                node = *headerAddr;
            }
            Obj &obj = *node->ptr;
            node = node->next;
            ++Set<Obj>::iterator::curCount;
            return obj;
        }
    };

    Reference<typename Set<Obj>::iterator> getBeginIterator() override {
        iterator *pit = new iterator(heads, heads[0], count);
        return Reference<typename Set<Obj>::iterator>(pit);
    }

    size_type size() const override {
        return count;
    }

    size_type capacity() const override {
        return count;
    }

    ~HashSet() {
        for (size_type i = 0; i < headerSize; ++i) {
            HashNode *node = heads[i], *next;
            while (node) {
                next = node->next;
                Allocator::deallocate(node);
                node = next;
            }
        }
        Allocator::deallocate(heads, headerSize);
    }

    void clear() override {
        for (size_type i = 0; i < headerSize; ++i) {
            HashNode *node = heads[i], *next;
            while (node) {
                next = node->next;
                Allocator::deallocate(node);
                node = next;
            }
        }
        Allocator::deallocate(heads, headerSize);
        heads = Allocator::allocate<HashNode *>(20);
        headerSize = 20;
        count = 0;
        memset(heads, 0, headerSize * sizeof(void**));  // clear array
    }

    HashSet() {
        memset(heads, 0, headerSize * sizeof(void**));  // clear array
    }

    HashSet(const HashSet<Obj> &rhs) : count(rhs.count), headerSize(rhs.headerSize), heads(Allocator::allocate<HashNode*>(headerSize)) {
        for (size_type i = 0; i < headerSize; ++i) {
            heads[i] = cloneLinkedList(rhs.heads[i]);
        }
    }

    HashSet(HashSet<Obj> &&rhs) noexcept : count(rhs.count), headerSize(rhs.headerSize), heads(rhs.heads) {
        rhs.heads = Allocator::allocate<HashNode*>(20);
        memset(rhs.heads, 0, headerSize * sizeof(void**));  // clear array
        rhs.headerSize = 20;
        rhs.count = 0;
    }

    HashSet<Obj> &operator=(const HashSet<Obj> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        for (size_type i = 0; i < headerSize; ++i) {
            HashNode *node = heads[i], *next;
            while (node) {
                next = node->next;
                Allocator::deallocate(node);
                node = next;
            }
        }
        count = rhs.count;
        headerSize = rhs.headerSize;
        heads = Allocator::allocate<HashNode*>(headerSize);
        for (size_type i = 0; i < headerSize; ++i) {
            heads[i] = cloneLinkedList(rhs.heads[i]);
        }
        return *this;
    }

    HashSet<Obj> &operator=(HashSet<Obj> &&rhs) noexcept {
        if (&rhs == this) {
            return *this;
        }
        for (size_type i = 0; i < headerSize; ++i) {
            HashNode *node = heads[i], *next;
            while (node) {
                next = node->next;
                Allocator::deallocate(node);
                node = next;
            }
        }
        count = rhs.count;
        headerSize = rhs.headerSize;
        heads = rhs.heads;
        rhs.clear();
        return *this;
    }

    void put(const Obj &obj) override {
        if (count == headerSize) {
            expand();
        }
        insertOne(obj);
    }

    void put(Obj &&obj) override {
        if (count == headerSize) {
            expand();
        }
        insertOne(std::forward<Obj>(obj));
    }

    void putAll(ContainerInterface<Obj> &rhs) override {
        auto pit = rhs.getBeginIterator();
        while(pit->hasNext()) {
            Obj &obj = pit->next();
            put(obj);
        }
    }

    void putAll(ContainerInterface<Obj> &&rhs) override {
        auto pit = rhs.getBeginIterator();
        while(pit->hasNext()) {
            Obj &obj = pit->next();
            put(std::move(obj));
        }
    }

    bool contains(const Obj &obj) override {
        return getNode(obj);
    }

    bool containsAll(ContainerInterface<Obj> &rhs) override {
        auto pit = rhs.getBeginIterator();
        while(pit->hasNext()) {
            Obj &p = pit->next();
            if (!contains(p)) {
                return false;
            }
        }
        return true;
    }

    void remove(const Obj &obj) override {
        hash_type code = (const_cast<Obj&>(obj)).hash();
        size_type index = (code % headerSize);
        HashNode *head = heads[index], *pre = nullptr;
        while (head) {
            if (head->hcode == code) {
                break;
            }
            pre = head;
            head = head->next;
        }
        if (head) {
            if (pre)
                pre->next = head->next;
            else
                heads[index] = head->next;
            Allocator::deallocate(head);
            --count;
        }
    }

    void removeAll(Set<Obj> &rhs) {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &obj = it->next();
            remove(obj);
        }
    }
};

#endif //MYSTL_HASHTABLE_HPP
