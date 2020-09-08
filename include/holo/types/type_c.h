//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef HOLO_TYPE_C_H
#define HOLO_TYPE_C_H

#include <holo/types/integral_constant/integral_c.h>
#include <type_traits>

HOLO_NS_BEGIN

template <typename T>
struct type_c_t {
   using type = T;
};

template <typename U, typename V>
inline constexpr auto operator==(type_c_t<U> const&, type_c_t<V> const&) noexcept {
   return bool_c<std::is_same_v<U, V>>;
}

template <typename U, typename V>
inline constexpr auto operator!=(type_c_t<U> const&, type_c_t<V> const&) noexcept {
   return bool_c<!std::is_same_v<U, V>>;
}

template <typename T>
constexpr type_c_t<T> type_c{};

template<typename T>
constexpr bool Is_Type_C = false;

template<typename T>
constexpr bool Is_Type_C<type_c_t<T>> = true;

HOLO_NS_END

#endif //HOLO_TYPE_C_H
