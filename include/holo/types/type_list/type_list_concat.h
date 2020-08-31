//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_CONCAT_H
#define HOLO_TYPE_LIST_CONCAT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<>
struct concat_algo<type_list_tag> {
   template <typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>) -> type_list<Xs..., Ys...> {
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_CONCAT_H
