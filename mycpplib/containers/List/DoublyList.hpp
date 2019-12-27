//
// Created by anarion on 2019/11/6.
//

#ifndef MYSTL_LIST_HPP
#define MYSTL_LIST_HPP

#include "allocator/Allocator.hpp"
#include <exceptions/containers/EmptyContainerException.h>
#include <exceptions/containers/IndexOutOfRangeException.h>
#include <new>
#include "List.hpp"

template <class Obj>
class DoublyList : public List<Obj> {
    typedef unsigned long size_type;

protected:
    struct Node {
        Node *next, *prev;
        Obj obj;
        Node() = default;
        Node(const Obj &obj, Node *next, Node *prev) : next(next), prev(prev), obj(obj) {}
        Node(Obj &&obj, Node *next, Node *prev) : next(next), prev(prev), obj(std::forward<Obj>(obj)) {}
    };

    Node head;
    size_type count = 0;

    Node *findNode(const Obj &obj) {
        Node *node = head.next;
        while (node != &head) {
            if (node->obj == obj) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    Node *move_forward_n(Node *begin, size_type index) {
        if (index >= count) {
            return nullptr;
        }
        auto node = begin;
        for (size_type i = 0; i < index; ++i) {
            node = node->next;
        }
        return node;
    }

    Node *move_back_n(Node *begin, size_type index) {
        if (index >= count) {
            return nullptr;
        }
        auto node = begin;
        for (size_type i = 0; i < index; ++i) {
            node = node->prev;
        }
        return node;
    }

    void removeNode(Node *node) {
        if (node->next == node || node->prev == node) {
            return;
        }
        --count;
        Node *next = node->next, *prev = node->prev;
        next->prev = prev;
        prev->next = next;
        Allocator::deallocate(node);
    }

    void addAfterNode(Node *node, const Obj &obj) {
        Node *next = node->next;
        Node *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(obj, next, node);
        next->prev = newnode;
        node->next = newnode;
        ++count;
    }

    void addAfterNode(Node *node, Obj &&obj) {
        Node *next = node->next;
        Node *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(std::forward<Obj>(obj), next, node);
        next->prev = newnode;
        node->next = newnode;
        ++count;
    }

    void addBeforeNode(Node *node, const Obj &obj) {
        Node *prev = node->prev, *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(obj, node, prev);
        prev->next = newnode;
        node->prev = newnode;
        ++count;
    }

    void addBeforeNode(Node *node, Obj &&obj) {
        Node *prev = node->prev, *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(std::forward<Obj>(obj), node, prev);
        prev->next = newnode;
        node->prev = newnode;
        ++count;
    }

    void updateIterator(Pointer<typename List<Obj>::iterator> &it, Node *node, size_type index, size_type size) {
        auto pit = dynamic_cast<iterator*>(it.operator->());
        pit->setCount(size);
        pit->setCurCount(index);
        pit->setNode(node);
    }

public:
    class iterator : public List<Obj>::iterator {
        Node *node;
    public:
        iterator(Node *n, size_type consize, size_type index = 0) : List<Obj>::iterator(consize, index), node(n) {}

        Obj &next() override {
            Obj &obj = node->obj;
            node = node->next;
            ++List<Obj>::iterator::curCount;
            return obj;
        }

        Node *getNode() {
            return node;
        }

        void setNode(Node *n) {
            node = n;
        }


    };

    Reference<typename List<Obj>::iterator> getBeginIterator() override {
        auto p = new iterator(head.next, count);
        return Reference<typename List<Obj>::iterator>(p);
    }

    DoublyList() {
        head.prev = &head;
        head.next = &head;
    }

    ~DoublyList() {
        Node *node = &head;
        while (node->next != &head) {
            auto p = node->next;
            Allocator::deallocate<Node>(p);
            node = p;
        }
    }

    void clear() override {
        Node *node = &head;
        while (node->next != &head) {
            auto p = node->next;
            Allocator::deallocate<Node>(node);
            node = p;
        }
        head.prev = &head;
        head.next = &head;
        count = 0;
    }

    size_type size() const override {
        return count;
    }

    size_type capacity() const override {
        return size();
    }

    // head tail operation
    void addFirst(const Obj & robj) override {
        auto p = Allocator::allocate<Node>();
        ::new (p) Node(robj, head.next, &head);
        head.next->prev = p;
        head.next = p;
        ++count;
    }

    void addFirst(Obj && rrobj) override {
        auto p = Allocator::allocate<Node>();
        new (p) Node(std::forward<Obj>(rrobj), head.next, &head);
        head.next->prev = p;
        head.next = p;
        ++count;
    }

    void add(const Obj & robj) override {
        Node *p = Allocator::allocate<Node>();
        new (p) Node(robj, &head, head.prev);
        head.prev->next = p;
        head.prev = p;
        ++count;
    }

    void add(Obj && rrobj) override {
        auto p = Allocator::allocate<Node>();
        new (p) Node(std::forward<Obj>(rrobj), &head, head.prev);
        head.prev->next = p;
        head.prev = p;
        ++count;
    }

    void add(size_type index, const Obj &obj) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        Node *node = move_back_n(head.next, index);
        addBeforeNode(node, obj);
    }

    void add(size_type index, Obj &&obj) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        Node *node = move_back_n(head.next, index);
        addBeforeNode(node, std::forward<Obj>(obj));
    }

    void addBefore(Pointer<typename List<Obj>::iterator> &it, const Obj &obj) override {
        auto &rit = dynamic_cast<iterator&>(*it);
        Node *node = rit.getNode();
        addBeforeNode(node, obj);
        updateIterator(it, node, rit.getIndex() + 1, size());
    }

    void addBefore(Pointer<typename List<Obj>::iterator> &it, Obj &&obj) override {
        auto &rit = dynamic_cast<iterator&>(*it);
        Node *node = rit.getNode();
        addBeforeNode(node, std::forward<Obj>(obj));
        updateIterator(it, node, rit.getIndex() + 1, size());
    }

    void addAfter(Pointer<typename List<Obj>::iterator> &it, const Obj &obj) override {
        auto &rit = dynamic_cast<iterator&>(*it);
        Node *node = rit.getNode();
        addAfterNode(node, obj);
        updateIterator(it, node, rit.getIndex(), size());
    }

    void addAfter(Pointer<typename List<Obj>::iterator> &it, Obj &&obj) override {
        auto &rit = dynamic_cast<iterator&>(*it);
        Node *node = rit.getNode();
        addAfterNode(node, std::forward<Obj>(obj));
        updateIterator(it, node, rit.getIndex(), size());
    }

    void addAll(List<Obj> &rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            add(it->next());
        }
    }

    void addAll(List<Obj> &&rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            add(std::move(it->next()));
        }
        rhs.clear();
    }

    void addAllAfterNode(Node *node, List<Obj> &rhs) {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            addAfterNode(node, it->next());
            node = node->next;
        }
    }

    void addAllAfterNode(Node *node, List<Obj> &&rhs) {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            addAfterNode(node, std::move(it->next()));
            node = node->next;
        }
        rhs.clear();
    }

    void addAllBeforeNode(Node *node, List<Obj> &rhs) {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            addBeforeNode(node, it->next());
        }
    }

    void addAllBeforeNode(Node *node, List<Obj> &&rhs) {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            addBeforeNode(node, std::move(it->next()));
        }
    }

    void addAll(size_type index, List<Obj> &rhs) override {
        Node *node = move_back_n(head.next, index);
        addAllAfterNode(node, rhs);
    }

    void addAll(size_type index, List<Obj> &&rhs) override {
        Node *node = move_back_n(head.next, index);
        addAllAfterNode(node, std::forward<List<Obj>>(rhs));
    }

    void addAllBefore(Pointer<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        Node *node = dynamic_cast<iterator&>(*it).getNode();
        addAllBeforeNode(node, rhs);
        updateIterator(it, node, it->getIndex() + rhs.size(), size());
    }

    void addAllBefore(Pointer<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        Node *node = dynamic_cast<iterator&>(*it).getNode();
        addAllBeforeNode(node, std::move(rhs));
        updateIterator(it, node, it->getIndex() + rhs.size(), size());
    }

    void addAllBefore(Pointer<typename List<Obj>::iterator> &it, DoublyList<Obj> &&rhs) {
        Node *node = dynamic_cast<iterator&>(*it).getNode()->prev, *next = node->next;
        node->next = rhs.head.next;
        next->prev = rhs.head.prev;
        rhs.head.next = &rhs.head;
        rhs.head.prev = &rhs.head;
        node->next->prev = node;
        next->prev->next = next;
        count += rhs.count;
        updateIterator(it, next, it->getIndex() + rhs.count, size());
        rhs.count = 0;
    }

    void addAllAfter(Pointer<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        Node *node = dynamic_cast<iterator&>(*it).getNode();
        addAllAfterNode(node, rhs);
        updateIterator(it, node, it->getIndex(), size());
    }

    void addAllAfter(Pointer<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        Node *node = dynamic_cast<iterator&>(*it).getNode();
        addAllBeforeNode(node, std::forward<List<Obj>>(rhs));
        updateIterator(it, node, it->getIndex(), size());
    }

    void addAllAfter(Pointer<typename List<Obj>::iterator> &it, DoublyList<Obj> &&rhs) {
        Node *node = dynamic_cast<iterator&>(*it).getNode(), *next = node->next;
        node->next = rhs.head.next;
        next->prev = rhs.head.prev;
        rhs.head.next = &rhs.head;
        rhs.head.prev = &rhs.head;
        node->next->prev = node;
        next->prev->next = next;
        count += rhs.count;
        rhs.count = 0;
        updateIterator(it, node, it->getIndex(), size());
    }

    void popBack() {
        if (count == 0) {
            throw EmptyContainerException();
        }
        auto p = head.prev;
        head.prev = head.prev->prev;
        head.prev->next = &head;
        Allocator::deallocate<Node>(p);
        --count;
    }

    void popFront() {
        if (count == 0) {
            throw EmptyContainerException();
        }
        auto p = head.next;
        head.next = head.next->next;
        head.next->next->prev = &head;
        Allocator::deallocate<Node>(p);
        --count;
    }

    Obj & getFirst() override {
        if (count == 0) {
            throw EmptyContainerException();
        }
        return head.next->obj;
    }

    Obj & getLast() override {
        if (count == 0) {
            throw EmptyContainerException();
        }
        return head.prev->obj;
    }

    Obj pollFirst() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        Obj ret(std::move(head.next->obj));
        popFront();
        return std::move(ret);
    }

    Obj pollLast() override {
        if (size() == 0) {
            throw EmptyContainerException();
        }
        Obj ret(std::move(head.prev->obj));
        popBack();
        return std::move(ret);
    }

    Obj & operator[](size_type index) override {
        if (index >= count) {
            throw IndexOutOfRangeException();
        }
        Node *p;
        if (index > count >> 1u) {
            index = count - index - 1;
            p = move_back_n(head.prev, index);
        } else {
            p = move_forward_n(head.next, index);
        }
        return p->obj;
    }

    // structural
    void pushBackAt(const Obj &obj, Node *node) {
        auto next = node->next;
        auto p = Allocator::allocate<Node>();
        ::new (p) Node(obj, next, node);
        next->prev = p;
        node->next = p;
        ++count;
    }

    void pushBackAt(Obj &&obj, Node *node) {
        auto next = node->next;
        auto p = Allocator::allocate<Node>();
        ::new (p) Node(std::forward<Obj>(obj), next, node);
        next->prev = p;
        node->next = p;
        ++count;
    }

    void pushFrontAt(const Obj &obj, Node *node) {
        auto prev = node->prev;
        auto p = Allocator::allocate<Node>();
        ::new (p) Node(obj, node, prev);
        prev->next = p;
        node->prev = p;
        ++count;
    }

    void pushFrontAt(Obj &&obj, Node *node) {
        auto prev = node->prev;
        auto p = Allocator::allocate<Node>();
        ::new (p) Node(std::forward<Obj>(obj), node, prev);
        prev->next = p;
        node->prev = p;
        ++count;
    }

    void popBackAt(Node *node) {
        if (count == 0) {
            throw EmptyContainerException();
        }
        --count;
        auto back = node->next;
        node->next = back->next;
        back->next->prev = node;
        Allocator::deallocate(back);
    }

    void popFrontAt(Node *node) {
        if (count == 0) {
            throw EmptyContainerException();
        }
        --count;
        auto prev = node->prev;
        node->prev = prev->prev;
        prev->prev->next = node;
        Allocator::deallocate(prev);
    }

    size_type indexOf(const Obj &obj) const override {
        auto node = head.next;
        size_type res = 0;
        while (node != &head) {
            if (obj == node->obj) {
                return res;
            }
            node = node->next;
            ++res;
        }
        return res;
    }

    size_type lastIndexOf(const Obj &obj) const override {
        auto node = head.prev;
        size_type res = count;
        while (node != &head) {
            if (obj == node->obj) {
                return res;
            }
            node = node->prev;
            --res;
        }
        return res;
    }

    bool contains(const Obj &obj) override {
        return findNode(obj);
    }

    bool containsAll(List<Obj> &rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            if (!contains(it->next())) {
                return false;
            }
        }
        return true;
    }

    void remove(size_type index) override {
        Node *node = move_back_n(head.next, index);
        removeNode(node);
    }

    void remove(Pointer<typename List<Obj>::iterator> &it) override {
        iterator *pit = dynamic_cast<iterator*>(it.operator->());
        Node *node = pit->getNode(), *next = node->next;
        size_type index = it->getIndex();
        removeNode(node);
        updateIterator(it, next, index, count);
    }

    void remove(const Obj &obj) override {
        Node *node = findNode(obj);
        if (!node) {
            return;
        }
        removeNode(node);
    }

    void removeAll(List<Obj> &rhs) override {

    }

    HashSet<Obj> toHashSet() override {

    }
};



#endif //MYSTL_LIST_HPP
