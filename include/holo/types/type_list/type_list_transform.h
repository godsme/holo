//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_TRANSFORM_H
#define HOLO_TYPE_LIST_TRANSFORM_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>

HOLO_NS_BEGIN

template<>
struct transform_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>)
   -> type_list<std::invoke_result_t<F, Xs>...> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_TRANSFORM_H
