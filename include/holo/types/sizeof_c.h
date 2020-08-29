//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_SIZEOF_C_H
#define HOLO_SIZEOF_C_H

#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

template<typename T>
constexpr integral_c<std::size_t, sizeof(T)> sizeof_c{};

HOLO_NS_END

#endif //HOLO_SIZEOF_C_H
