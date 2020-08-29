//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_PREPEND_H
#define HOLO_TYPE_LIST_PREPEND_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>

HOLO_NS_BEGIN

template<>
struct prepend_algo<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X, type_list<Xs...>) {
      return type_list<std::decay_t<X>, Xs...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_PREPEND_H
