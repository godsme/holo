//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REVERSE_H
#define GRAPH_REVERSE_H

#include <holo/holo_ns.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename RESULT, typename ... Ts>
   struct reverse_impl {
      using type = RESULT;
   };

   template<typename RESULT, typename H, typename ... Ts>
   struct reverse_impl<RESULT, H, Ts...> {
      using type = typename reverse_impl<typename RESULT::template prepend_type<H>, Ts...>::type;
   };
}

template <typename ... Ts>
constexpr auto reverse(tuple<Ts...> const&) {
   return typename detail::reverse_impl<tuple<>, Ts...>::type{};
}

HOLO_NS_END

#endif //GRAPH_REVERSE_H
