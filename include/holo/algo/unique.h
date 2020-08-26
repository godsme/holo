//
// Created by Darwin Yuan on 2020/8/14.
//

#ifndef GRAPH_UNIQUE_H
#define GRAPH_UNIQUE_H

#include <holo/types/integral_c.h>
#include <holo/algo/contains.h>

HOLO_NS_BEGIN

namespace detail {

   template<typename H, typename RESULT>
   constexpr bool Contains = std::is_same_v<bool_c_t<true>, decltype(contains(std::declval<H>(), RESULT{}))>;

   template<typename RESULT, typename = void, typename ... Ts>
   struct unique_impl {
      using type = RESULT;
   };

   template<typename RESULT, typename H, typename ... Ts>
   struct unique_impl<RESULT, std::enable_if_t<Contains<H, RESULT>>, H, Ts...> {
      using type = typename unique_impl<RESULT, void, Ts...>::type;
   };

   template<typename RESULT, typename H, typename ... Ts>
   struct unique_impl<RESULT, std::enable_if_t<!Contains<H, RESULT>>, H, Ts...> {
      using type = typename unique_impl<typename RESULT::template append_type<H>, void, Ts...>::type;
   };
}

template<typename ... Ts>
using unique_t = typename detail::unique_impl<tuple<>, void, Ts...>::type;

struct unique_c {
   template<typename ... Ts>
   constexpr auto operator()(tuple<Ts...>) const {
      return unique_t<Ts...>{};
   }

   constexpr auto operator()() const {
      return [this](auto stream) {
         return operator()(stream);
      };
   }
};

constexpr unique_c unique{};


HOLO_NS_END

#endif //GRAPH_UNIQUE_H
