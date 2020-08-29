//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_PARTITION_H
#define HOLO_TYPE_LIST_PARTITION_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/pair.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename FIRST, typename SECOND, typename ... Ts>
   struct partition_impl {
      using type = pair<FIRST, SECOND>;
   };

   template<typename PRED, typename ... Xs, typename ... Ys, typename H, typename ... Ts>
   struct partition_impl<PRED, type_list<Xs...>, type_list<Ys...>, H, Ts...> {
      using type = std::conditional_t<
         Is_Pred_Satisfied<PRED, H>,
         typename partition_impl<PRED, type_list<Xs..., H>, type_list<Ys...>, Ts...>::type,
         typename partition_impl<PRED, type_list<Xs...>, type_list<Ys..., H>, Ts...>::type>;
   };
}

template<typename F, typename ... Ts>
using TL_partition_t = typename detail::partition_impl<std::decay_t<F>, type_list<>, type_list<>, Ts...>::type;

template<>
struct partition_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F&&, type_list<Xs...>) {
      return TL_partition_t<F, Xs...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_PARTITION_H
