//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FIND_IF_H
#define GRAPH_FIND_IF_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/maybe.h>
#include <holo/algo/detail/pred.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

namespace detail {
   template <typename PRED, typename = void, typename ... Ts>
   struct find_if_impl {
      using type = nothing_t;
   };

   template <typename PRED, typename H, typename ... Ts>
   struct find_if_impl<PRED, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = H;
   };

   template <typename PRED, typename H, typename ... Ts>
   struct find_if_impl<PRED, std::enable_if_t<!Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename find_if_impl<PRED, void, Ts...>::type;
   };
}

template<typename F, typename ... Ts>
using find_if_t = typename detail::find_if_impl<F, void, Ts...>::type;

struct find_if_c {
private:
   template<typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return find_if_t<F, Ts...>{};
   }

public:
   template<typename F, typename ... Ts>
   constexpr auto operator()(F&&, tuple<Ts...> stream) const {
      return invoke<F>(stream);
   }

   template<typename F>
   constexpr auto operator()(F&&) const {
      __return_invoke(F);
   }
};

constexpr find_if_c find_if{};

HOLO_NS_END

#endif //GRAPH_FIND_IF_H
