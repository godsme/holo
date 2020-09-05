//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_NON_COMPARABLE_H
#define HOLO_NON_COMPARABLE_H

#include <holo/types/integral_constant/integral_c.h>

HOLO_NS_BEGIN

template<typename X, typename Y>
constexpr bool Non_Comparable = !std::is_same_v<X, Y> && !std::is_constructible_v<X, Y> && !std::is_constructible_v<Y, X>;

template<typename X, typename Y, typename = std::enable_if_t<Non_Comparable<X, Y>>>
constexpr auto operator==(X const&, Y const&) {
   return false_c;
}

template<typename X, typename Y, typename = std::enable_if_t<Non_Comparable<X, Y>>>
constexpr auto operator!=(X const&, Y const&) {
   return true_c;
}

HOLO_NS_END

#endif //HOLO_NON_COMPARABLE_H
