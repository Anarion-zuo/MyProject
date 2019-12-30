//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_HASHSET_HPP
#define REFERENCELIB_HASHSET_HPP

#include "../Set.hpp"

template <typename T>
class HashSet : public Set<T> {
protected:
    struct Node {
        Pointer<T> ptr;
        hash_type hash;
        Node *next;

        explicit Node(hash_type hash = 0, Pointer<T> ptr = nullptr, Node *next = nullptr) : hash(hash), ptr(ptr), next(next) {}
        ~Node() = default;
    };

    Node *heads;
    size_type headsCount = 20, count = 0;

    size_type headsIndex(T *p) {
        return p->hash() % headsCount;
    }

    void expand() {
        size_type oldheadscount = headsCount;
        headsCount <<= 1ul;
        Node *oldheads = heads;
        heads = new Node[headsCount];
        for (size_type i = 0; i < headsCount; ++i) {
            Node *node = heads[i].next;
            while (node) {
                put(node->ptr.operator->());
                node = node->next;
            }
        }
        delete[] oldheads;
    }

    void put(T *p) {
        hash_type hash = p->hash();
        size_type index = hash % headsCount;
        Node *next = heads[index].next;
        heads[index].next = new Node(hash, p, next);
    }

    Node *findNode(T *p) {
        hash_type hash = p->hash();
        size_type index = hash % headsCount;
        Node *node = heads[index].next;
        while (node) {
            if (node->hash == hash) {
                if (node->ptr->equals(p)) {
                    return node;
                }
            }
            node = node->next;
        }
        return nullptr;
    }

    void removeNode(T *p) {
        hash_type hash = p->hash();
        size_type index = hash % headsCount;
        Node *node = &heads[index], *next = node->next;
        while (next) {
            if (next->hash == hash) {
                if (next->ptr->equals(p)) {
                    // node found
                    node->next = next->next;
                    delete next;
                    return;
                }
            }
            node = next;
            next = next->next;
        }
    }

    typedef typename Container<T>::iterator parent_iterator;
public:
    class iterator : public parent_iterator {
        Node *node;
        size_type headerIndex = 0;
        HashSet<T> *_this;
    public:
        explicit iterator(size_type size, HashSet<T> *_this) : parent_iterator(size), _this(_this), node(_this->heads[0].next) {}
        Pointer<T> next() override {
            ++parent_iterator::index;
            while (!node) {
                ++headerIndex;
                node = _this->heads[headerIndex].next;
            }
            auto p = node->ptr;
            node = node->next;
            return p;
        }
    };

    Pointer<parent_iterator> getBeginIterator() override {
        return new iterator(count, this);
    }

    HashSet() : heads(new Node[20]) {}
    ~HashSet() {
        for (size_type i = 0; i < headsCount; ++i) {
            Node *node = heads[i].next;
            while (node) {
                Node *next = node->next;
                delete node;
                node = next;
            }
        }
        delete[] heads;
    }

    bool contains(Pointer<T> p) override {
        return findNode(p.operator->());
    }

    void remove(Pointer<T> p) override {
        --count;
        removeNode(p.operator->());
    }

    void removeAll(Pointer<Container<T>> rhs) override {

    }

    void clear() override {
        for (size_type i = 0; i < headsCount; ++i) {
            Node *node = heads[i].next;
            while (node) {
                Node *next = node->next;
                delete node;
                node = next;
            }
        }
        delete[] heads;
        heads = new Node[20];
        headsCount = 20;
        count = 0;
    }

    size_type size() const override {
        return count;
    }

    void put(Pointer<T> p) override {
        if (headsCount == count) {
            expand();
        }
        put(p.operator->());
        ++count;
    }

    void putAll(Pointer<Container<T>> rhs) override {

    }
};


#endif //REFERENCELIB_HASHSET_HPP
