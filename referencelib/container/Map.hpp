//
// Created by 左钰 on 2019/12/29.
//

#ifndef REFERENCELIB_MAP_HPP
#define REFERENCELIB_MAP_HPP


#include "../base/Pointer.hpp"

template <typename Key, typename Val>
class Map : public Object {
public:
    class Entry : public Object {
    protected:
        Pointer<Key> key;
        Pointer<Val> val;
    public:
        Entry(Pointer<Key> key, Pointer<Val> val) : key(key), val(val) {}

        Pointer<Key> getKey() {
            return key;
        }

        Pointer<Val> getVal() {
            return val;
        }

        bool equals(Pointer<Object> rhs) override {
            return key->equals(rhs);
        }

        hash_type hash() override {
            return key->hash();
        }

        Pointer<SString> toString() override {
            Pointer<SString> str = new SString;
            char lb = '(', rb = ')', co = ',';
            str->append(&lb, 1);
            Pointer<SString> k = key->toString(), v = val->toString();
            str->append(k);
            str->append(&co, 1);
            str->append(v);
            str->append(&rb, 1);
            k.release();
            v.release();
            return str;
        }
    };

    virtual void put(Pointer<Key> key, Pointer<Val> val) = 0;
    virtual bool containsKey(Pointer<Key> key) = 0;
    virtual void removeKey(Pointer<Key> key) = 0;
    virtual Pointer<Val> get(Pointer<Key> key) = 0;
};


#endif //REFERENCELIB_MAP_HPP
