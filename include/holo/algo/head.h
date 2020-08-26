//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_HEAD_H
#define GRAPH_HEAD_H

#include <holo/holo_ns.h>
#include <holo/types/tuple.h>
#include <holo/types/size_c.h>
#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

template <typename TUPLE>
constexpr auto empty(const TUPLE& tuple) {
   return bool_c<std::tuple_size_v<TUPLE> == 0>;
}

template <typename TUPLE>
constexpr auto size(const TUPLE& tuple) {
   return holo::size_c<tuple_size_v<TUPLE>>;
}

template <typename ... Ts>
constexpr auto head(tuple<Ts...> const&) {
   return typename tuple<Ts...>::head{};
}

template <typename ... Ts>
constexpr auto tail(tuple<Ts...> const&) {
   return typename tuple<Ts...>::tail{};
}

HOLO_NS_END

#endif //GRAPH_HEAD_H
