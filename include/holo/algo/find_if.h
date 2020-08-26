//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FIND_IF_H
#define GRAPH_FIND_IF_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/maybe.h>
#include <holo/algo/detail/pred.h>

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

struct find_if_c {
   template<typename ... Ts, typename F>
   constexpr auto operator()(F&&, tuple<Ts...>) const {
      return typename detail::find_if_impl<F, void, Ts...>::type{};
   }

   template<typename F>
   constexpr auto operator()(F&& f) const {
      return [func = std::move(f), this](auto stream) {
         return operator()(func, stream);
      };
   }
};

constexpr find_if_c find_if{};

HOLO_NS_END

#endif //GRAPH_FIND_IF_H
