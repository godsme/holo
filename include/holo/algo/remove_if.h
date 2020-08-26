//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REMOVE_IF_H
#define GRAPH_REMOVE_IF_H

#include <holo/types/tuple.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename RESULT, typename = void, typename ... Ts>
   struct remove_if_impl {
      using type = RESULT;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
      struct remove_if_impl<PRED, RESULT, std::enable_if_t<!Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename remove_if_impl<PRED, typename RESULT::template append_type<H>, void, Ts...>::type;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct remove_if_impl<PRED, RESULT, std::enable_if_t<Is_Pred_Satisfied <PRED, H>>, H, Ts...> {
      using type = typename remove_if_impl<PRED, RESULT, void, Ts...>::type;
   };
}

template<typename ... Ts, typename F>
constexpr auto remove_if(F&& f, const tuple<Ts...>&) {
   return typename detail::remove_if_impl<F, tuple<>, void, Ts...>::type{};
}

HOLO_NS_END

#endif //GRAPH_REMOVE_IF_H
