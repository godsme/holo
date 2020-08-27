//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_TRANSFORM_H
#define GRAPH_TRANSFORM_H

#include <holo/types/type_c.h>
#include <holo/algo/partial_apply.h>
#include <type_traits>

HOLO_NS_BEGIN

namespace detail {
   template<typename F, typename RESULT, typename ... Ts>
   struct transform_impl {
      using type = RESULT;
   };

   template<typename F, typename RESULT, typename H, typename ... Ts>
   struct transform_impl<F, RESULT, H, Ts...> {
      using type =
         typename transform_impl<F
            , typename RESULT::template append_type<std::invoke_result_t<F, H>>
            , Ts...>::type;
   };
}

template<typename F, typename ... Ts>
using transform_t = typename detail::transform_impl<std::decay_t<F>, tuple<>, Ts...>::type;

struct transform_c {
private:
   template <typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return transform_t<F, Ts...>{};
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

constexpr transform_c transform{};

HOLO_NS_END

#endif //GRAPH_TRANSFORM_H
