//
// Created by 左钰 on 2019/12/7.
//

#ifndef MYCPPLIB_LIST_HPP
#define MYCPPLIB_LIST_HPP

#include <containers/ContainerInterface.hpp>
#include <featurers/UseAllocator.h>
#include <wrappers/Pointer/Pointer.hpp>
#include <containers/Set/HashSet.hpp>

typedef unsigned long size_type;

template <typename Obj>
class List : public ContainerInterface<Obj> {
public:
    typedef typename ContainerInterface<Obj>::iterator iterator;
    virtual ~List() = default;

    virtual void add(const Obj &obj) = 0;
    virtual void add(Obj &&obj) = 0;
    virtual void add(size_type index, const Obj &obj) = 0;
    virtual void add(size_type index, Obj &&obj) = 0;
    virtual void addBefore(Pointer<iterator> &it, const Obj &obj) = 0;
    virtual void addBefore(Pointer<iterator> &it, Obj &&obj) = 0;
    virtual void addAfter(Pointer<iterator> &it, const Obj &obj) = 0;
    virtual void addAfter(Pointer<iterator> &it, Obj &&obj) = 0;

//    virtual void addLast(const Obj &obj) = 0;
//    virtual void addLast(Obj &&obj) = 0;
    virtual void addFirst(const Obj &obj) = 0;
    virtual void addFirst(Obj &&obj) = 0;

    virtual Obj &getFirst() = 0;
    virtual Obj &getLast() = 0;
    virtual Obj pollFirst() = 0;
    virtual Obj pollLast() = 0;

    virtual void addAll(List<Obj> &rhs) = 0;
    virtual void addAll(size_type index, List<Obj> &rhs) = 0;
    virtual void addAll(List<Obj> &&rhs) = 0;
    virtual void addAll(size_type index, List<Obj> &&rhs) = 0;
    virtual void addAllBefore(Pointer<iterator> &it, List<Obj> &rhs) = 0;
    virtual void addAllBefore(Pointer<iterator> &it, List<Obj> &&rhs) = 0;
    virtual void addAllAfter(Pointer<iterator> &it, List<Obj> &rhs) = 0;
    virtual void addAllAfter(Pointer<iterator> &it, List<Obj> &&rhs) = 0;

    virtual void remove(const Obj &obj) = 0;
    virtual void remove(size_type index) = 0;
    virtual void remove(Pointer<iterator> &it) = 0;
    virtual void removeAll(List<Obj> &rhs) = 0;

    virtual bool contains(const Obj &obj) = 0;
    virtual bool containsAll(List<Obj> &rhs) = 0;

    virtual Obj &operator[](size_type index) = 0;

    virtual size_type indexOf(const Obj &obj) const = 0;
    virtual size_type lastIndexOf(const Obj &obj) const = 0;

    virtual HashSet<Obj> toHashSet() = 0;

};


#endif //MYCPPLIB_LIST_HPP
