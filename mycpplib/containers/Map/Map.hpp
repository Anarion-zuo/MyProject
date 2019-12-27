//
// Created by anarion on 2019/11/11.
//

#ifndef MYSTL_MAP_HPP
#define MYSTL_MAP_HPP

#include <base-classes/Object.h>

template <class Key, class Val>
struct MapEntry : public Hashable {
    Key *key;
    Val *val;

    MapEntry() : key(nullptr), val(nullptr) {}
    MapEntry(const Key &key, const Val &val) : key(new Key(key)), val(new Val(val)) {}
    MapEntry(Key &&key, Val &&val) : key(new Key(std::forward<Key>(key))), val(new Key(std::forward<Val>(val))) {}
    MapEntry(const MapEntry<Key, Val> &rhs) : key(new Key(*rhs.key)), val(new Val(*rhs.val)) {}
    MapEntry(MapEntry<Key, Val> &&rhs) noexcept : key(rhs.key), val(rhs.val) {
        rhs.key = nullptr;
        rhs.val = nullptr;
    }
    ~MapEntry() {
        delete key;
        delete val;
    }
    bool operator==(const MapEntry<Key, Val> &rhs) const {
        return *rhs.key == *key;
    }
    bool operator<(const MapEntry<Key, Val> &rhs) const {
        return *key < *rhs.key;
    }
    MapEntry<Key, Val> &operator=(const MapEntry<Key, Val> &rhs) {
        if (&rhs == this) {
            return *this;
        }
        *key = *rhs.key;
        *val = *rhs.val;
        return *this;
    }
    MapEntry<Key, Val> &operator=(MapEntry<Key, Val> &&rhs) noexcept {
        if (&rhs == this) {
            return *this;
        }
        key = rhs.key;
        val = rhs.val;
        rhs.key = nullptr;
        rhs.val = nullptr;
        return *this;
    }
    Key &getKey() {
        return *key;
    }
    Val &getVal() {
        return *val;
    }

    hash_type hash() const override {
        return key->hash();
    }
};
template <typename Key, typename Val>
class Map : public Object {
public:
    virtual void put(const Key &key, const Val &val) = 0;
    virtual void put(Key &&key, Val &&val) = 0;
    virtual void put(const Key &key, Val &&val) = 0;
    virtual void put(Key &&key, const Val &val) = 0;
    virtual bool containsKey(const Key &key) = 0;
    virtual bool containsKey(Key &&key) = 0;
    virtual void remove(const Key &key) = 0;
    virtual void remove(Key &&key) = 0;
    virtual Val &operator[](const Key &key) = 0;
    virtual Val &operator[](Key &&key) = 0;

    Val &get(const Key &key) {
        return operator[](key);
    }

    Val &get(Key &&key) {
        return operator[](std::forward<Key>(key));
    }
};


#endif //MYSTL_MAP_HPP
