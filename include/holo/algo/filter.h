//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <holo/holo_ns.h>
#include <holo/types/type_c.h>
#include <holo/algo/partial_apply.h>
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

template<typename F, typename ... Ts>
using filter_t = typename detail::filter_impl<F, tuple<>, void, Ts...>::type;

struct filter_c {
private:
   template <typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return filter_t<F, Ts...>{};
   }

public:
   template <typename F, typename ... Ts>
   constexpr auto operator()(F&&, tuple<Ts...> stream) const {
      return invoke<F>(stream);
   }

   template <typename F>
   constexpr auto operator()(F&&) const {
      __return_invoke(F);
   }
};

constexpr filter_c filter{};

HOLO_NS_END

#endif //GRAPH_FILTER_H
