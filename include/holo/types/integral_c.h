//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_INTEGRAL_C_H
#define GRAPH_INTEGRAL_C_H

#include <holo/holo_ns.h>
#include <type_traits>

HOLO_NS_BEGIN

template<typename T, T V>
struct integral_c {
   constexpr operator T() const { return V; }
};

template<bool V>
using bool_c_t = integral_c<bool, V>;

template<bool V>
constexpr bool_c_t<V> bool_c{};

template<typename T, T V1, T V2>
inline constexpr auto operator==(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<V1 == V2>;
}

template<typename T, T V1, T V2>
inline constexpr auto operator!=(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<V1 != V2>;
}

template<typename T, T V1, T V2>
inline constexpr auto operator<(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<V1 < V2>;
}

template<typename T, T V1, T V2>
inline constexpr auto operator<=(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<V1 <= V2>;
}

template<typename T, T V1, T V2>
inline constexpr auto operator>(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<(V1 > V2)>;
}

template<typename T, T V1, T V2>
inline constexpr auto operator>=(integral_c<T, V1> const& lhs, integral_c<T, V2> const& rhs) {
   return bool_c<(V1 >= V2)>;
}

HOLO_NS_END

#endif //GRAPH_INTEGRAL_C_H
