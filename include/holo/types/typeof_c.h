//
// Created by Darwin Yuan on 2020/9/8.
//

#ifndef HOLO_TYPEOF_C_H
#define HOLO_TYPEOF_C_H

#include <holo/types/type_c.h>
#include <type_traits>

HOLO_NS_BEGIN

template<typename T>
inline constexpr auto typeof_c(type_c_t<T>) noexcept -> T { return {}; }

HOLO_NS_END

#endif //HOLO_TYPEOF_C_H
