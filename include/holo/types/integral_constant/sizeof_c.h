//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_SIZEOF_C_H
#define HOLO_SIZEOF_C_H

#include <holo/types/integral_constant/integral_c.h>

HOLO_NS_BEGIN

template<typename T>
using sizeof_t = integral_c<std::size_t, sizeof(T)>;


template<typename T>
constexpr sizeof_t<T> sizeof_c{};

template<typename T>
constexpr auto sizeof_type_c(type_c_t<T>) -> sizeof_t<T> { return {}; }

HOLO_NS_END

#endif //HOLO_SIZEOF_C_H
