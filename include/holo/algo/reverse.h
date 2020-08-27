//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REVERSE_H
#define GRAPH_REVERSE_H

#include <holo/holo_ns.h>
#include <holo/algo/partial_apply.h>

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

template<typename ... Ts>
using reverse_t = typename detail::reverse_impl<tuple<>, Ts...>::type;

struct reverse_c {
private:
   template <typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return reverse_t<Ts...>{};
   }

public:
   template <typename ... Ts>
   constexpr auto operator()(tuple<Ts...> stream) const {
      return invoke(stream);
   }

   constexpr auto operator()() const {
      __return_invoke_0();
   }
};

constexpr reverse_c reverse{};

HOLO_NS_END

#endif //GRAPH_REVERSE_H
