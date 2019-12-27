//
// Created by 左钰 on 2019/12/12.
//

#ifndef MYCPPLIB_LISTSTACK_HPP
#define MYCPPLIB_LISTSTACK_HPP

#include <containers/List/DoublyList.hpp>
#include "Stack.hpp"

template <typename Obj>
class ListStack : public Stack<Obj> {
protected:
    DoublyList<Obj> doublyLinkedList;
public:
    ListStack() = default;

    void put(const Obj &obj) override {
        doublyLinkedList.addFirst(obj);
    }

    void put(Obj &&obj) override {
        doublyLinkedList.addFirst(std::forward<Obj>(obj));
    }

    Obj poll() override {
        return doublyLinkedList.pollLast();
    }
};


#endif //MYCPPLIB_LISTSTACK_HPP
