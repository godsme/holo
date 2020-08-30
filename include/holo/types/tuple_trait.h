//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_TUPLE_TRAIT_H
#define HOLO_TUPLE_TRAIT_H

#include <holo/holo_ns.h>
#include <type_traits>

HOLO_NS_BEGIN

template<typename T, template<typename ...> typename C>
struct tuple_trait;

template<typename T, template<typename ...> typename C>
using tuple_trait_t = typename tuple_trait<std::decay_t<T>, C>::type;

HOLO_NS_END

#endif //HOLO_TUPLE_TRAIT_H
