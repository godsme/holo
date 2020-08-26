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

struct remove_if_c {
   template<typename ... Ts, typename F>
   constexpr auto operator()(F&& f, const tuple<Ts...>&) const {
      return typename detail::remove_if_impl<F, tuple<>, void, Ts...>::type{};
   }

   template<typename F>
   constexpr auto operator()(F&& f) const {
      return [func = std::move(f), this](auto stream) {
         return operator()(func, stream);
      };
   }
};

constexpr remove_if_c remove_if{};


HOLO_NS_END

#endif //GRAPH_REMOVE_IF_H
