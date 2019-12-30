//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_LISTQUEUE_H
#define REFERENCELIB_LISTQUEUE_H

#include "../Queue.hpp"
#include "../List/LinkedList.hpp"

template <typename T>
class ListQueue : public Queue<T> {
protected:
    LinkedList<T> list;
public:
    ListQueue() : list() {}

    void put(Pointer<T> ptr) override {
        list.addFirst(ptr);
    }

    Pointer<T> poll() override {
        return list.poll();
    }

    bool isEmpty() const override {
        return !list.size();
    }
};


#endif //REFERENCELIB_LISTQUEUE_H
