//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_MAYBE_H
#define HOLO_MAYBE_H

#include <holo/types/integral_constant/integral_c.h>
#include <type_traits>

HOLO_NS_BEGIN

struct nothing_t {};
constexpr nothing_t nothing{};

constexpr auto operator==(nothing_t const&, nothing_t const&) {
   return bool_c<true>;
}

constexpr auto operator!=(nothing_t const&, nothing_t const&) {
   return bool_c<false>;
}

template<typename T, typename = std::enable_if_t<!std::is_same_v<T, nothing_t>>>
constexpr auto operator==(T const&, nothing_t const&) {
   return bool_c<false>;
}

template<typename T, typename = std::enable_if_t<!std::is_same_v<T, nothing_t>>>
constexpr auto operator!=(T const&, nothing_t const&) {
   return bool_c<true>;
}

template<typename T, typename = std::enable_if_t<!std::is_same_v<T, nothing_t>>>
constexpr auto operator==(nothing_t const&, T const&) {
   return bool_c<false>;
}

template<typename T, typename = std::enable_if_t<!std::is_same_v<T, nothing_t>>>
constexpr auto operator!=(nothing_t const&, T const&) {
   return bool_c<true>;
}

template<typename T>
constexpr auto is_nothing(T const& v) {
   return v == nothing;
}

HOLO_NS_END

#endif //HOLO_MAYBE_H
