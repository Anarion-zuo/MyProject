//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_HASHMAP_HPP
#define REFERENCELIB_HASHMAP_HPP

#include "../Map.hpp"
#include "../Set/HashSet.hpp"

template <typename Key, typename Val>
class HashMap : public Map<Key, Val>, public HashSet<typename Map<Key, Val>::Entry>{
    typedef typename Map<Key, Val>::Entry Entry;
    typedef typename Container<Entry>::iterator parent_iterator;
public:
    Pointer<parent_iterator> getBeginIterator() override {
        return HashSet<Entry>::getBeginIterator();
    }

    void put(Pointer<Key> key, Pointer<Val> val) override {
        HashSet<Entry>::put(new Entry(key, val));
    }

    bool containsKey(Pointer<Key> key) override {
        Pointer<Entry> en = new Entry(key, nullptr);
        bool ret = HashSet<Entry>::contains(en);
        en.release();
        return ret;
    }

    void removeKey(Pointer<Key> key) override {
        Pointer<Entry> en = new Entry(key, nullptr);
        HashSet<Entry>::remove(en);
        en.release();
    }

    Pointer<Val> get(Pointer<Key> key) override {
        Pointer<Entry> en = new Entry(key, nullptr);
        auto node = HashSet<Entry>::findNode(en.operator->());
        Pointer<Val> ret = node->ptr->getVal();
        en.release();
        return ret;
    }

    Pointer<SString> toString() override {
        return HashSet<Entry>::toString();
    }
};


#endif //REFERENCELIB_HASHMAP_HPP
