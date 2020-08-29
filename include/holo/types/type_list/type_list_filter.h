//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FILTER_H
#define HOLO_TYPE_LIST_FILTER_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename RESULT, typename = void, typename ... Ts>
   struct filter_impl {
      using type = RESULT;
   };

   template<typename PRED, typename ... Ys, typename H, typename ... Ts>
   struct filter_impl<PRED, type_list<Ys...>, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, type_list<Ys..., H>, void, Ts...>::type;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<!Is_Pred_Satisfied <PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, RESULT, void, Ts...>::type;
   };
}

template<typename F, typename ... Xs>
using TL_filter_t = typename detail::filter_impl<F, type_list<>, void, Xs...>::type;

template<>
struct filter_algo<type_list_tag> {
   template<typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) {
      return TL_filter_t<F, Xs...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FILTER_H
