//
// Created by anarion on 2019/12/19.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef MYCPPLIB_TREEMAP_HPP
#define MYCPPLIB_TREEMAP_HPP

#include "Map.hpp"
#include <containers/Set/TreeSet.hpp>
#include <utility>

template <typename Key, typename Val>
class TreeMap : public Map<Key, Val>, public TreeSet<MapEntry<Key, Val>> {
public:
    TreeMap() = default;

    void put(const Key &key, const Val &val) override {
        TreeSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(key, val));
    }

    void put(Key &&key, Val &&val) override {
        TreeSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(std::forward<Key>(key), std::forward<Val>(val)));

    }

    void put(const Key &key, Val &&val) override {
        TreeSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(key, std::forward<Val>(val)));
    }

    void put(Key &&key, const Val &val) override {
        TreeSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(std::forward<Key>(key), val));
    }

    bool containsKey(const Key &key) override {
        return TreeSet<MapEntry<Key, Val>>::contains(MapEntry<Key, Val>(key, Val()));
    }

    bool containsKey(Key &&key) {
        return TreeSet<MapEntry<Key, Val>>::contains(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
    }

    void remove(const Key &key) override {
        TreeSet<MapEntry<Key, Val>>::remove(MapEntry<Key, Val>(key, Val()));
    }

    void remove(Key &&key) {
        TreeSet<MapEntry<Key, Val>>::remove(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
    }

    Val &operator[](const Key &key) override {
        auto *p = TreeSet<MapEntry<Key, Val>>::tree.search_tree_node(MapEntry<Key, Val>(key, Val()));
        if (p == RedBlackTree<MapEntry<Key, Val>>::NIL) {
            throw IndexOutOfRangeException();
        }
        return *p->key.val;
    }

    Val &operator[](Key &&key) override {
        auto *p = TreeSet<MapEntry<Key, Val>>::tree.search_tree_node(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
        if (p == RedBlackTree<MapEntry<Key, Val>>::NIL) {
            throw IndexOutOfRangeException();
        }
        return *p->key.val;
    }
};


#endif //MYCPPLIB_TREEMAP_HPP
