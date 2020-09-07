//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_TYPE_TRANSFORM_H
#define HOLO_TYPE_TRANSFORM_H

#include <holo/holo_ns.h>
#include <type_traits>

HOLO_NS_BEGIN

template<typename T, template<typename ...> typename C>
struct type_transform;

template<typename T, template<typename ...> typename C>
using type_transform_t = typename type_transform<std::decay_t<T>, C>::type;

HOLO_NS_END

#endif //HOLO_TYPE_TRANSFORM_H
