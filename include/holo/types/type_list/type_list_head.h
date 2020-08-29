//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_HEAD_H
#define HOLO_TYPE_LIST_HEAD_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<>
struct head_algo<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(type_list<X, Xs...>) {
      return X{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_HEAD_H
