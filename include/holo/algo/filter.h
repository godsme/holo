//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <holo/holo_ns.h>
#include <holo/types/type_c.h>
#include <type_traits>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename RESULT, typename = void, typename ... Ts>
   struct filter_impl {
      using type = RESULT;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, typename RESULT::template append_type<H>, void, Ts...>::type;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<!Is_Pred_Satisfied <PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, RESULT, void, Ts...>::type;
   };
}

struct filter_c {
   template <typename ... Ts, typename F>
   constexpr auto operator()(F&& f, tuple<Ts...>) const {
      return typename detail::filter_impl<F, tuple<>, void, Ts...>::type{};
   }

   template <typename F>
   constexpr auto operator()(F&& f) const {
      return [func = std::move(f), this](auto stream) {
         return operator()(func, stream);
      };
   }
};

constexpr filter_c filter{};

HOLO_NS_END

#endif //GRAPH_FILTER_H
