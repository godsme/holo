//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_CONTAINS_H
#define HOLO_TYPE_LIST_CONTAINS_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>

HOLO_NS_BEGIN

template<>
struct contains_algo<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X, type_list<Xs...>) {
      return bool_c<(std::is_same_v<Xs, std::decay_t<X>> || ...)>;
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_CONTAINS_H
