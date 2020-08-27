//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REMOVE_IF_H
#define GRAPH_REMOVE_IF_H

#include <holo/types/tuple.h>
#include <holo/algo/partial_apply.h>

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

template<typename F, typename ... Ts>
using remove_if_t = typename detail::remove_if_impl<F, tuple<>, void, Ts...>::type;

struct remove_if_c {
   template<typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return remove_if_t<F, Ts...>{};
   }

   template<typename F, typename ... Ts>
   constexpr auto operator()(F&&, tuple<Ts...> stream) const {
      return invoke<F>(stream);
   }

   template<typename F>
   constexpr auto operator()(F&&) const {
      __return_invoke(F);
   }
};

constexpr remove_if_c remove_if{};


HOLO_NS_END

#endif //GRAPH_REMOVE_IF_H
