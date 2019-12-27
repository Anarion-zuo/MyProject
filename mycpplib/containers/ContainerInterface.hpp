//
// Created by 左钰 on 2019/12/7.
//

#ifndef MYCPPLIB_CONTAINERINTERFACE_HPP
#define MYCPPLIB_CONTAINERINTERFACE_HPP

#include <base-classes/Object.h>
#include <wrappers/Pointer/Reference.hpp>
#include <featurers/UseAllocator.h>

template <typename Obj>
class ContainerInterface : public Object {
public:
    typedef unsigned long size_type;

    virtual ~ContainerInterface() = default;

    // sizes
    virtual size_type size() const = 0;
    virtual size_type capacity() const = 0;

    bool isEmpty() const {
        return size() == 0;
    }

    // clear
    virtual void clear() = 0;


    class iterator : public UseAllocator, public Hashable {
    protected:
        size_type curCount, count;
    public:
        explicit iterator(size_type consize, size_type index = 0) : count(consize), curCount(index) {}

        virtual ~iterator() = default;
        bool hasNext() {
            return curCount < count;
        }
        virtual Obj &next() = 0;
        size_type getIndex() const {
            return curCount;
        }
        void setCurCount(size_type n) {
            curCount = n;
        }
        void setCount(size_type n) {
            count = n;
        }
    };
    virtual Reference <iterator> getBeginIterator() = 0;

};


#endif //MYCPPLIB_CONTAINERINTERFACE_HPP
