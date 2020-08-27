//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_TRANSFORM_H
#define GRAPH_TRANSFORM_H

#include <holo/types/type_c.h>
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

struct transform_c {
   template <typename ... Ts, typename F>
   constexpr auto operator()(F&&, tuple<Ts...>) const {
      return typename detail::transform_impl<std::decay_t<F>, tuple<>, Ts...>::type{};
   }

   template <typename F>
   constexpr auto operator()(F&& f) const {
      return [func = std::move(f), this](auto stream) {
         return (*this)(func, stream);
      };
   }
};

constexpr transform_c transform{};

HOLO_NS_END

#endif //GRAPH_TRANSFORM_H
