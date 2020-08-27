//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_PARTITION_H
#define GRAPH_PARTITION_H

#include <holo/types/tuple.h>
#include <type_traits>
#include <holo/types/pair.h>
#include <holo/algo/detail/pred.h>
#include <holo/algo/partial_apply.h>

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
   template <typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return partition_t<F, Ts...>{};
   }

   template <typename F, typename ... Ts>
   constexpr auto operator()(F&&, tuple<Ts...> stream) const {
      return invoke<F>(stream);
   }

   template <typename F>
   constexpr auto operator()(F&& f) const {
      __return_invoke(F);
   }
};

constexpr partition_c partition{};

HOLO_NS_END

#endif //GRAPH_PARTITION_H
