//
// Created by anarion on 2019/12/19.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef MYCPPLIB_TREEMAP_HPP
#define MYCPPLIB_TREESET_HPP


#include <containers/Base/RedBlackTree.hpp>
#include "Set.hpp"

template <typename T>
class TreeSet : public Set<T> {
protected:
    RedBlackTree<T> tree;
    size_type count = 0;
public:

class iterator : public Set<T>::iterator {
    RedBlackTreeNode<T> *node;
    RedBlackTree<T> *tree;
public:
    explicit iterator(size_type consize, size_type index, RedBlackTreeNode<T> *node, RedBlackTree<T> *_this) : Set<T>::iterator(consize, index), node(node), tree(_this) {}

    T &next() override {
        T &obj = node->key;
        node = tree->get_successor(node);
        ++Set<T>::iterator::curCount;
        return obj;
    }
};

    TreeSet() = default;

    unsigned long size() const override {
        return count;
    }

    unsigned long capacity() const override {
        return size();
    }

    void clear() override {
        tree.clear();
        count = 0;
    }

    void put(const T &obj) override {
        tree.insert_key(obj);
        ++count;
    }

    void put(T &&obj) override {
        tree.insert_key(std::forward<T>(obj));
        ++count;
    }

    void putAll(ContainerInterface<T> &rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            T &obj = it->next();
            put(obj);
        }
        count += rhs.size();
    }

    void putAll(ContainerInterface<T> &&rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            T &obj = it->next();
            put(std::move(obj));
        }
        count += rhs.size();
    }

    void remove(const T &obj) override {
        tree.delete_key(obj);
        --count;
    }

    bool contains(const T &obj) override {
        return tree.search_element(obj);
    }

    bool containsAll(ContainerInterface<T> &rhs) override {
        auto it = rhs.getBeginIterator();
        while (it->hasNext()) {
            T &obj = it->next();
            if (!contains(obj)) {
                return false;
            }
        }
        return true;
    }

    Reference<typename Set<T>::iterator> getBeginIterator() override {
        RedBlackTreeNode<T> *head = tree.get_minmum(tree.get_root());
        return Reference<typename Set<T>::iterator>(new iterator(count, 0, head, &tree));
    }
};


#endif //MYCPPLIB_TREEMAP_HPP
