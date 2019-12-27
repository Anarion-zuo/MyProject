//
// Created by 左钰 on 2019/12/13.
//

#ifndef MYCPPLIB_TUPLE_HPP
#define MYCPPLIB_TUPLE_HPP

#include <featurers/UseAllocator.h>

template <typename ...Tn>
struct Tuple {

};

template <typename T0, typename ...Tn>
struct Tuple<T0, Tn...> : public Tuple<Tn...>{
    T0 obj;
    explicit Tuple(const T0 &o0, const Tn &...os) : Tuple<Tn...>(os...), obj(o0) {}
    explicit Tuple(T0 &&o0, Tn &&...os) : Tuple<Tn...>(std::forward<Tn>(os)...), obj(std::forward<T0>(obj)) {}

    auto &get(unsigned long index) -> decltype() {
        if (index > 0) {
            return Tuple<Tn...>::get(index - 1);
        }
        return obj;
    }
};

template <>
struct Tuple<> : public UseAllocator {

};
//
//template <unsigned long index, typename T0, typename ...Tn>
//auto &get(Tuple<T0, Tn...> &tuple) {
//    if (index == 0) {
//        return get<T0, Tn...>(tuple);
//    }
//    auto& newt = dynamic_cast<Tuple<Tn...>&>(tuple);
//    return get<index - 1, Tn...>(newt);
//}
//
//template <typename T0, typename ...Tn>
//auto &get(Tuple<T0, Tn...> &tuple) {
//    return tuple.obj;
//}
//
//template <unsigned long index>
//int get(Tuple<> &tuple) {
//    throw IndexOutOfRangeException();
//}


#endif //MYCPPLIB_TUPLE_HPP
