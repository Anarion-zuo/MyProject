//
// Created by anarion on 2019/12/1.
//

#ifndef MYCPPLIB_SINGLYLIST_HPP
#define MYCPPLIB_SINGLYLIST_HPP

#include <new>
#include <base-classes/Object.h>
#include <exceptions/containers/EmptyContainerException.h>
#include <exceptions/containers/IndexOutOfRangeException.h>
#include "List.hpp"

template <typename Obj>
class SinglyList : public List<Obj> {
protected:
    struct Node {
        Node *next;
        Obj obj;

        explicit Node(const Obj &obj, Node *next = nullptr) : next(next), obj(obj) {}
        explicit Node(Obj &&obj, Node *next = nullptr) : next(next), obj(std::forward<Obj>(obj)) {}
        Node(const Node &rhs) : next(nullptr), obj(rhs.obj) {}

        Node *clone() const {
            Node *res = Allocator::allocate<Node>();
            ::new (res) Node(obj);
            Node *srcn = this, *dstn = res;
            while(srcn->next) {
                Node *next = srcn->next;
                dstn->next = Allocator::allocate<Node>();
                dstn = dstn->next;
                ::new (dstn) Node(*next);
                srcn = srcn->next;
            }
        }
    };

    size_type count = 0;
    Node *head = nullptr, *end = nullptr;

    Node * move_back_n(Node *node, size_type index) {
        for (size_type i = 0; i < index; ++i) {
            if (!node) {
                return nullptr;
            }
            node = node->next;
        }
        return node;
    }

    void delList(Node *node) {
        while (node) {
            auto next = node->next;
            Allocator::deallocate(node);
            node = next;
        }
    }

    void clearAfterMove() {
        head = nullptr;
        end = nullptr;
        count = 0;
    }

    void addFirstNode(const Obj &obj) {
        head = Allocator::allocate<Node>();
        ::new (head) Node(obj);
        end = head;
        count = 1;
    }

    void addFirstNode(Obj &&obj) {
        head = Allocator::allocate<Node>();
        ::new (head) Node(std::forward<Obj>(obj));
        end = head;
        count = 1;
    }

    void addAfterNode(Node *node, const Obj &obj) {
        Node *next = node->next, *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(obj, next);
        node->next = newnode;
        if (node == end) {
            end = end->next;
        }
    }

    void addAfterNode(Node *node, Obj &&obj) {
        Node *next = node->next, *newnode = Allocator::allocate<Node>();
        ::new (newnode) Node(std::forward<Obj>(obj), next);
        node->next = newnode;
        if (node == end) {
            end = end->next;
        }
    }

    void removeAfterNode(Node *node) {
        --count;
        Node *next = node->next;
        if (next == end) {
            end = node;
        }
        node->next = next->next;
        Allocator::deallocate(next);
    }

    void removeHead() {
        Node *node = head;
        if (end == head) {
            end = head->next;
        }
        head = head->next;
        --count;
        Allocator::deallocate(node);
    }

    void removeEnd() {
        Node *node = head;
        if (!node) {
            return;
        }
        while (node->next != end) {
            node = node->next;
        }
        removeAfterNode(node);
    }

    void updateIterator(Reference<typename List<Obj>::iterator> &it, Node *node, size_type index, size_type size) {
        auto *pit = dynamic_cast<iterator*>(it.operator->());
        pit->setNode(node);
        pit->setCurCount(index);
        pit->setCount(size);
    }

    Node *findNode(const Obj &obj) {
        Node *node = head;
        while (node) {
            if (node->obj == obj) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    Node *findNodeBefore(const Obj &obj) {
        Node *node = head;
        if (!node) {
            return nullptr;
        }
        while (node->next) {
            if (node->next->obj == obj) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

public:
    class iterator : public List<Obj>::iterator {
        Node *node;
    public:
        iterator(Node *node, size_type count, size_type index = 0) : List<Obj>::iterator(count, index), node(node) {}

        Obj &next() override {
            Obj &obj = node->obj;
            node = node->next;
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
        iterator *pit = new iterator(head, count);
        return Reference<typename List<Obj>::iterator>(pit);
    }

    SinglyList() = default;
    ~SinglyList() {
        delList(head);
    }
    SinglyList(const SinglyList<Obj> &rhs) : count(rhs.count) {
        if (!count) {
            return;
        }
        head = rhs.clone();
        end = move_back_n(head, count - 1);
    }
    SinglyList(SinglyList<Obj> &&rhs) noexcept : head(rhs.head), count(rhs.count), end(rhs.end) {
        rhs.clearAfterMove();
    }
    SinglyList<Obj> &operator=(const SinglyList<Obj> &rhs) {
        if (this == &rhs) {
            return *this;
        }
        delList(head);
        if (rhs.isEmpty()) {
            clear();
            return *this;
        }
        head = rhs.head->clone();
        count = rhs.count;
        end = move_back_n(head, count - 1);
        return *this;
    }
    SinglyList<Obj> &operator=(SinglyList<Obj> &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delList(head);
        head = rhs.head;
        count = rhs.count;
        end = rhs.end;
        rhs.clearAfterMove();
        return *this;
    }

    size_type size() const override {
        return count;
    }

    size_type capacity() const override {
        return size();
    }

    void clear() override {
        delList(head);
        head = nullptr;
        end = nullptr;
        count = 0;
    }

    void addFirst(const Obj &obj) override {
        if (!head) {
            addFirstNode(obj);
            return;
        }
        Node *old = head;
        head = Allocator::allocate<Node>();
        ::new (head) Node(obj, old);
        ++count;
    }

    void addFirst(Obj &&obj) override {
        if (!head) {
            addFirstNode(std::forward<Obj>(obj));
            return;
        }
        Node *old = head;
        head = Allocator::allocate<Node>();
        ::new (head) Node(std::forward<Obj>(obj), old);
        ++count;
    }

    void add(const Obj &obj) override {
        if (!head) {
            addFirstNode(obj);
            return;
        }
        addAfterNode(end, obj);
        end = end->next;
    }

    void add(Obj &&obj) override {
        if (!head) {
            addFirstNode(std::forward<Obj>(obj));
            return;
        }
        addAfterNode(end, std::forward<Obj>(obj));
        end = end->next;
    }

    void add(size_type index, const Obj &obj) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (index == 0) {
            addFirst(obj);
            return;
        }
        if (index == size()) {
            add(obj);
            return;
        }
        Node *node = move_back_n(head, index - 1);
        addAfterNode(node, obj);
    }

    void add(size_type index, Obj &&obj) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (index == 0) {
            addFirst(std::forward<Obj>(obj));
            return;
        }
        if (index == size()) {
            add(std::forward<Obj>(obj));
            return;
        }
        Node *node = move_back_n(head, index - 1);
        addAfterNode(node, std::forward<Obj>(obj));
    }

    void addBefore(Reference<typename List<Obj>::iterator> &it, const Obj &obj) override  {
        Node *node = dynamic_cast<iterator*>(it.operator->())->getNode();
        if (it->getIndex() == 0) {
            throw IndexOutOfRangeException();
        }
        add(it->getIndex() - 1, obj);
        updateIterator(it, node, it->getIndex() + 1, count);
    }

    void addBefore(Reference<typename List<Obj>::iterator> &it, Obj &&obj) override {
        Node *node = dynamic_cast<iterator*>(it.operator->())->getNode();
        if (it->getIndex() == 0) {
            throw IndexOutOfRangeException();
        }
        add(it->getIndex() - 1, std::forward<Obj>(obj));
        updateIterator(it, node, it->getIndex() + 1, count);
    }

    void addAfter(Reference<typename List<Obj>::iterator> &it, const Obj &obj) override {
        Node *node = dynamic_cast<iterator*>(it.operator->())->getNode();
        addAfterNode(node, obj);
        updateIterator(it, node, it->getIndex(), count);
    }

    void addAfter(Reference<typename List<Obj>::iterator> &it, Obj &&obj) override {
        Node *node = dynamic_cast<iterator*>(it.operator->())->getNode();
        addAfterNode(node, std::forward<Obj>(obj));
        updateIterator(it, node, it->getIndex(), count);
    }

    void addAll(List<Obj> &rhs) override {
        auto it {rhs.getBeginIterator()};
        while (it->hasNext()) {
            Obj &obj = it->next();
            add(obj);
        }
    }

    void addAll(List<Obj> &&rhs) override {
        auto it {rhs.getBeginIterator()};
        while (it->hasNext()) {
            Obj &obj = it->next();
            add(std::move(obj));
        }
        rhs.clear();
    }

    void addAll(SinglyList<Obj> &&rhs) {
        end->next = rhs.head;
        count += rhs.count;
        end = rhs.end;
        rhs.clearAfterMove();
    }

    void addAllFirst(List<Obj> &rhs) {
        if (rhs.isEmpty()) {
            return;
        }
        auto it = rhs.getBeginIterator();
        Obj &first = it->next();
        addFirst(first);
        while (it->hasNext()) {
            Obj &obj = it->next();
            addAfterNode(head, obj);
        }
    }

    void addAllFirst(List<Obj> &&rhs) {
        if (rhs.isEmpty()) {
            return;
        }
        auto it = rhs.getBeginIterator();
        Obj &first = it->next();
        addFirst(first);
        while (it->hasNext()) {
            Obj &obj = it->next();
            addAfterNode(head, std::forward<Obj>(obj));
        }
    }

    void addAll(size_type index, List<Obj> &rhs) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (index == size()) {
            addAll(rhs);
            return;
        }
        if (index == 0) {
            addAllFirst(rhs);
            return;
        }
        Node *node = move_back_n(head, index - 1);
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &obj = it->next();
            addAfterNode(node, obj);
            node = node->next;
        }
    }

    void addAll(size_type index, List<Obj> &&rhs) override {
        if (index > size()) {
            throw IndexOutOfRangeException();
        }
        if (index == size()) {
            addAll(std::forward<List<Obj>>(rhs));
            return;
        }
        if (index == 0) {
            addAllFirst(std::forward<List<Obj>>(rhs));
            return;
        }
        Node *node = move_back_n(head, index - 1);
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &obj = it->next();
            addAfterNode(node, std::move(obj));
            node = node->next;
        }
    }

    void addAllBefore(Reference<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        size_type index = it->getIndex();
        addAll(index, rhs);
    }
    void addAllBefore(Reference<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        size_type index = it->getIndex();
        addAll(index, std::forward<List<Obj>>(rhs));
    }
    void addAllAfter(Reference<typename List<Obj>::iterator> &it, List<Obj> &rhs) override {
        auto pit = dynamic_cast<iterator*>(it.operator->());
        Node *node = pit->getNode();
        auto rit = rhs.getBeginIterator();
        while (rit->hasNext()) {
            Obj &obj = rit->next();
            addAfterNode(node, obj);
            node = node->next;
        }
    }

    void addAllAfter(Reference<typename List<Obj>::iterator> &it, List<Obj> &&rhs) override {
        auto pit = dynamic_cast<iterator*>(it.operator->());
        Node *node = pit->getNode();
        auto rit = rhs.getBeginIterator();
        while (rit->hasNext()) {
            Obj &obj = rit->next();
            addAfterNode(node, std::move(obj));
            node = node->next;
        }
        rhs.clear();
    }

    Obj pollFirst() override {
        Obj ret(std::move(head->obj));
        removeHead();
        return std::move(ret);
    }

    Obj pollLast() override {
        Obj ret(std::move(head->obj));
        removeHead();
        return std::move(ret);
    }

    void pop() {
        if (!head) {
            throw EmptyContainerException();
        }
        auto next = head->next;
        Allocator::deallocate(head);
        head = next;
    }

    Obj & getFirst() override {
        if (!head) {
            throw EmptyContainerException();
        }
        return head->obj;
    }

    Obj &getLast() override {
        if (!end) {
            throw EmptyContainerException();
        }
        return end->obj;
    }

    bool contains(const Obj &obj) override {
        return findNode(obj);
    }

    bool containsAll(List<Obj> &rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            Obj &obj = it->next();
            if (!contains(obj)) {
                return false;
            }
        }
        return true;
    }

    void remove(const Obj &obj) override {
        if (head->obj == obj) {
            removeHead();
            return;
        }
        Node *node = findNodeBefore(obj);
        if (node == nullptr) {
            return;
        }
        removeAfterNode(node);
    }

    void remove(size_type index) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        if (!index) {
            removeHead();
            return;
        }
        Node *node = move_back_n(head, index - 1);
        removeAfterNode(node);
    }

    void remove(Reference<typename List<Obj>::iterator> &it) override {
        auto pit = dynamic_cast<iterator*>(it.operator->());
        Node *next = pit->getNode()->next;
        remove(it->getIndex());
        updateIterator(it, next, it->getIndex(), count);
    }

    Obj &operator[](size_type index) override {
        if (index >= size()) {
            throw IndexOutOfRangeException();
        }
        Node *node = move_back_n(head, index);
        return node->obj;
    }

    size_type indexOf(const Obj &obj) const override {
        Node *node = head;
        size_type index = 0;
        while (node) {
            if (node->obj == obj) {
                return index;
            }
            ++index;
            node = node->next;
        }
        return index;
    }

    size_type lastIndexOf(const Obj &obj) const override {
        return count - indexOf(obj);
    }

    void removeAll(List<Obj> &rhs) override {

    }

    HashSet<Obj> toHashSet() override {

    }
};


#endif //MYCPPLIB_SINGLYLIST_HPP
