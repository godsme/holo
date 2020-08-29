//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FIND_IF_H
#define HOLO_TYPE_LIST_FIND_IF_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/maybe.h>

HOLO_NS_BEGIN

namespace detail {
   template <typename PRED, typename ... Xs>
   struct find_if_impl {
      using type = nothing_t;
   };

   template <typename PRED, typename X, typename ... Xs>
   struct find_if_impl<PRED, X, Xs...> {
      using type = std::conditional_t<Is_Pred_Satisfied<PRED, X>,
         X,
         typename find_if_impl<PRED, Xs...>::type>;
   };
}

template<typename F, typename ... Xs>
using TL_find_if_t = typename detail::find_if_impl<F, Xs...>::type;

template <> struct find_if_algo<type_list_tag> {
   template<typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) {
      return TL_find_if_t<F, Xs...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FIND_IF_H
