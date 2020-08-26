//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONTAINS_H
#define GRAPH_CONTAINS_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

template <typename ... Ts, typename T>
constexpr auto contains(T&& value, tuple<Ts...> const&) {
   return bool_c<(std::is_same_v<Ts, std::decay_t<T>> || ...)>;
}

HOLO_NS_END

#endif //GRAPH_CONTAINS_H
