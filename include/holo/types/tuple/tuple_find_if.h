//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_FIND_IF_H
#define HOLO_TUPLE_FIND_IF_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/detail/filter_result.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/maybe.h>

HOLO_NS_BEGIN
namespace detail {
   template<std::size_t N, typename PRED, typename ... Xs>
   struct find_helper {
      using type = size_c_t<N>;
   };

   template<std::size_t N, typename PRED, typename X, typename ... Xs>
   struct find_helper<N, PRED, X, Xs...> {
      using type = std::conditional_t<
         detail::Is_Pred_Satisfied<PRED, X>,
            size_c_t<N>,
            typename find_helper<N+1, PRED, Xs...>::type>;
   };
}

template<> struct find_if_algo<tuple_tag> {
   template<typename PRED, typename ... Xs>
   constexpr static auto apply(PRED const& pred, tuple<Xs...> const& xs) {
      constexpr auto N = detail::find_helper<0, PRED, Xs...>::type::value();
      if constexpr (N >= sizeof...(Xs)) {
         return nothing;
      } else {
         return get<N>(xs);
      }
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_FIND_IF_H
