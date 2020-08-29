//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_PAIR_H
#define GRAPH_PAIR_H

#include <holo/types/type_list/type_list.h>
#include <type_traits>

HOLO_NS_BEGIN

template<typename T1, typename T2>
struct type_pair : type_list<T1, T2> {
   using first  = T1;
   using second = T2;
};

template<typename T1, typename T2>
constexpr type_pair<type_c_t< T1>, type_c_t<T2>> type_pair_t{};

template<typename T1, typename T2>
constexpr auto make_pair(T1 const&, T2 const&) {
   return type_pair < std::decay_t<T1>, std::decay_t<T2>>{};
}

template<typename T1, typename T2>
constexpr auto first(type_pair < T1, T2 > const&) {
   return T1{};
}

template<typename T1, typename T2>
constexpr auto second(type_pair < T1, T2 > const&) {
   return T2{};
}

HOLO_NS_END

#endif //GRAPH_PAIR_H
