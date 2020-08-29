//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_SIZE_C_H
#define HOLO_SIZE_C_H

#include <holo/types/integral_c.h>
#include <type_traits>

HOLO_NS_BEGIN

template <size_t V>
using size_c_t = integral_c<size_t, V>;

template <size_t V>
constexpr size_c_t<V> size_c{};

HOLO_NS_END

#endif //HOLO_SIZE_C_H
