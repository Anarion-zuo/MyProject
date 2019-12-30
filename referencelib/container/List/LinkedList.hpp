//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_LINKEDLIST_HPP
#define REFERENCELIB_LINKEDLIST_HPP

#include "../List.h"

template <typename T>
class LinkedList : public List<T> {
protected:
    struct Node {
        T *ptr;
        Node *next, *prev;
        explicit Node(T *p, Node *next = nullptr, Node *prev = nullptr) : ptr(p), next(next), prev(prev) {}
        ~Node() = default;
    };

    Node head;
    size_type count = 0;

    typedef typename Container<T>::iterator parent_iterator;
public:
    class iterator : public parent_iterator {
        Node *node;
    public:
        iterator(Node *node, size_type size, size_type index = 0) : parent_iterator(size, index), node(node) {}

        Pointer<T> next() {
            ++parent_iterator::index;
            T *p = node->ptr;
            node = node->next;
            return p;
        }
    };

    Pointer<parent_iterator> getBeginIterator() override {
        return new iterator(head.next, count);
    }

    LinkedList() : head(nullptr) {
        head.next = &head;
        head.prev = &head;
    }
    ~LinkedList() {
        Node *node = head.next;
        while (node != &head) {
            Node *next = node->next;
            delete node;
            node = next;
        }
    }

    void add(Pointer<T> p) override {
        auto node = new Node(p.operator->(), &head, head.prev);
        head.prev->next = node;
        head.prev = node;
        ++count;
    }

    void addFirst(Pointer<T> p) override {
        auto node = new Node(p.operator->(), head.next, &head);
        head.next->prev = node;
        head.next = node;
        ++count;
    }

    void addAll(Pointer<Container<T>> rhs) override {

    }

    void remove(Pointer<T> p) override {
        Node *node = &head;
        --count;
        while (node->next != &head) {
            if (p->equals(node->next->ptr)) {
                Node *del = node->next;
                node->next = del->next;
                del->next->prev = node;
                delete del;
            }
        }
    }

    void removeAll(Pointer<Container<T>> rhs) override {

    }

    void clear() override {

    }

    void add(Pointer<T> p, size_type index) override {
        Node *node = &head;

    }

    Pointer<T> get(size_type index) override {
        return Pointer<T>();
    }

    Pointer<T> poll() override {
        --count;
        Node *node = head.prev;
        T *p = node->ptr;
        head.prev = node->prev;
        node->prev->next = &head;
        delete node;
        return p;
    }

    size_type size() const override {
        return count;
    }

    size_type indexOf(Pointer<Object> p) override {
        Node *node = head.next;
        size_type i = 0;
        while (node != &head) {
            if (p->equals(node->ptr)) {
                return i;
            }
            ++i;
            node = node->next;
        }
        return count;
    }
};


#endif //REFERENCELIB_LINKEDLIST_HPP
