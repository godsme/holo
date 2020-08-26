//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_PARTITION_H
#define GRAPH_PARTITION_H

#include <holo/types/type_c.h>
#include <holo/types/tuple.h>
#include <holo/algo/concat.h>
#include <type_traits>
#include <holo/types/integral_c.h>
#include <holo/types/pair.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename FIRST, typename SECOND, typename = void, typename ... Ts>
   struct partition_impl {
      using type = pair<FIRST, SECOND>;
   };

   template<typename PRED, typename FIRST, typename SECOND, typename H, typename ... Ts>
   struct partition_impl<PRED, FIRST, SECOND, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename partition_impl<PRED, typename FIRST::template append_type<H>, SECOND, void, Ts...>::type;
   };

   template<typename PRED, typename FIRST, typename SECOND, typename H, typename ... Ts>
   struct partition_impl<PRED, FIRST, SECOND, std::enable_if_t<!Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename partition_impl<PRED, FIRST, typename SECOND::template append_type<H>, void, Ts...>::type;
   };
}

template<typename F, typename ... Ts>
using partition_t = typename detail::partition_impl<std::decay_t<F>, tuple<>, tuple<>, void, Ts...>::type;

struct partition_c {
   template <typename ... Ts, typename F>
   constexpr auto operator()(F&&, tuple<Ts...>) const {
      return partition_t<F, Ts...>{};
   }

   template <typename ... Ts, typename F>
   constexpr auto operator()(F&& f) const {
      return [ func = std::move(f), this](auto stream) {
         return operator()(func, stream);
      };
   }
};

constexpr partition_c partition{};

HOLO_NS_END

#endif //GRAPH_PARTITION_H
