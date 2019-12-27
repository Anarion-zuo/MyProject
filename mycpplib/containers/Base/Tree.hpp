//
// Created by anarion on 2019/12/3.
//

#ifndef MYCPPLIB_TREE_HPP
#define MYCPPLIB_TREE_HPP

#include <base-classes/Object.h>
#include <new>

template <typename Obj>
class Tree : public Object {
protected:
    struct Node {
        Obj obj;
        Node *left, *right, *parent;

        Node(const Obj &obj, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : obj(obj), parent(parent), left(left), right(right) {}

        Node(Obj &&obj, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : obj(std::forward<Obj>(obj)), parent(parent), left(left), right(right) {}

        Node(const Node &rhs) : obj(rhs.obj), left(nullptr), right(nullptr), parent(nullptr) {}

        Node(Node &&rhs) noexcept : obj(std::move(rhs.obj)), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *head = nullptr;
public:

};


#endif //MYCPPLIB_TREE_HPP
