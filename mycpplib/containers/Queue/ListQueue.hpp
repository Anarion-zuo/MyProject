//
// Created by 左钰 on 2019/12/10.
//

#ifndef MYCPPLIB_LISTQUEUE_HPP
#define MYCPPLIB_LISTQUEUE_HPP

#include <containers/List/DoublyList.hpp>
#include <featurers/UnCopiable.h>
#include <featurers/UseAllocator.h>
#include "Queue.hpp"

template <typename Obj>
class ListQueue : public Queue<Obj>, public UnCopiable, public UseAllocator {
protected:
    DoublyList<Obj> doublyLinkedList;
public:
    ListQueue() = default;
    ListQueue(ListQueue<Obj> &&rhs) noexcept : doublyLinkedList(std::move(rhs)) {}
    ListQueue &operator=(ListQueue<Obj> &&rhs) noexcept {
        doublyLinkedList = std::move(rhs.doublyLinkedList);
        return *this;
    }

    size_type size() const override {
        return doublyLinkedList.size();
    }

    size_type capacity() const override {
        return doublyLinkedList.capacity();
    }

    void clear() override {
        doublyLinkedList.clear();
    }

    void put(const Obj &obj) override {
        doublyLinkedList.addFirst(obj);
    }

    void put(Obj &&obj) override {
        doublyLinkedList.addFirst(std::forward<Obj>(obj));
    }

    Obj poll() override {
        return doublyLinkedList.pollLast();
    }

    bool isEmpty() const override {
        return doublyLinkedList.isEmpty();
    }
};


#endif //MYCPPLIB_LISTQUEUE_HPP
