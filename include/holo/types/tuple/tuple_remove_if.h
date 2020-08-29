//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_REMOVE_IF_H
#define HOLO_TUPLE_REMOVE_IF_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/detail/filter_result.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct remove_if_algo<tuple_tag> {
   template<typename PRED, typename ... Xs>
   constexpr static auto apply(PRED const& pred, tuple<Xs...> const& xs) {
      using Indices = detail::filter_indices<!detail::Is_Pred_Satisfied<PRED, Xs>...>;
      return detail::filter_result<Indices>(xs, std::make_index_sequence<Indices::cached_indices.size()>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_REMOVE_IF_H
