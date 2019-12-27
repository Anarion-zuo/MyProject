
#ifndef MYSTL_HASHMAP_HPP
#define MYSTL_HASHMAP_HPP

#include "containers/Set/HashSet.hpp"
#include "Map.hpp"
#include <functors/unary_functor.h>
#include <featurers/Hashable.h>

typedef unsigned long HashCode;


template <class Key, class Val>
class HashMap : public HashSet<MapEntry<Key, Val>>, public Map<Key, Val> {
    typedef unsigned long size_type;

public:
    class iterator : public HashSet<MapEntry<Key, Val>>::iterator {};

    HashMap() : HashSet<MapEntry<Key, Val>>() {}
    explicit HashMap(const HashMap<Key, Val> &rhs) : HashSet<MapEntry<Key, Val>>(rhs) {}
    explicit HashMap(HashMap<Key, Val> &&rhs) noexcept : HashSet<MapEntry<Key, Val>>(std::forward<HashMap<Key, Val>>(rhs)) {}
    HashMap<Key, Val> &operator=(const HashMap<Key, Val> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        HashSet<MapEntry<Key, Val>>::operator=(rhs);
        return *this;
    }
    HashMap<Key, Val> &operator=(HashMap<Key, Val> &&rhs) noexcept {
         if (&rhs == this) {
            return *this;
        }
        HashSet<MapEntry<Key, Val>>::operator=(std::forward<HashMap<Key, Val>, Key>(rhs));
        return *this;
    }

    // map operations
    void put(const Key &key, const Val &val) {
        HashSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(key, val));
    }

    void put(const Key &key, Val &&val) {
        HashSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(key, std::forward<Val>(val)));
    }

    void put(Key &&key, const Val &val) {
        HashSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(std::forward<Key>(key), val));
    }

    void put(Key &&key, Val &&val) {
        HashSet<MapEntry<Key, Val>>::put(MapEntry<Key, Val>(std::forward<Key>(key), std::forward<Val>(val)));
    }

    bool containsKey(const Key &key) {
        return HashSet<MapEntry<Key, Val>>::
        contains(MapEntry<Key, Val>(key, Val()));
    }

    bool containsKey(Key &&key) {
        return HashSet<MapEntry<Key, Val>>::
        contains(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
    }

    void remove(const Key &key) {
        HashSet<MapEntry<Key, Val>>::
        remove(MapEntry<Key, Val>(key, Val()));
    }

    void remove(Key &&key) {
        HashSet<MapEntry<Key, Val>>::
        remove(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
    }

    Val &operator[](const Key &key) override {
        auto pair = HashSet<MapEntry<Key, Val>>::
        getNode(MapEntry<Key, Val>(key, Val()));
        return pair->ptr->val;
    }

    Val &operator[](Key &&key) override {
        auto pair = HashSet<MapEntry<Key, Val>>::
        getNode(MapEntry<Key, Val>(std::forward<Key>(key), Val()));
        return pair->ptr->val;
    }


};

#endif