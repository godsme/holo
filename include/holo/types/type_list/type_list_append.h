//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_APPEND_H
#define HOLO_TYPE_LIST_APPEND_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>

HOLO_NS_BEGIN

template<>
struct append_algo<type_list_tag> {
   template <typename T, typename ... Ts>
   constexpr static auto apply(T, type_list<Ts...>)
      -> type_list<Ts..., std::decay_t<T>> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_APPEND_H
