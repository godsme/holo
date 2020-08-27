//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_SORT_H
#define GRAPH_SORT_H

#include <holo/algo/partition.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename LT, typename ... Ts>
   struct sort_impl {
      using type = tuple<>;
   };

   template<typename LT, typename H, typename ... Ts>
   struct sort_impl<LT, H, Ts...> {
      constexpr static auto lt = [](auto elem){ return decltype(std::declval<LT>()(elem, H{})){}; };
      using PRED = decltype(lt);
      template<typename ... TS> using sort_more = typename sort_impl<LT, TS...>::type;
      using parts = partition_t<PRED, Ts...>;
      using lesser  = typename parts::first::template export_to<sort_more>;
      using greater = typename parts::second::template export_to<sort_more>;
      using type = typename lesser::template append_type<H>::template append_list<greater>;
   };
}

template<typename LT, typename ... Ts>
using sort_t = typename detail::sort_impl<LT, Ts...>::type;

struct sort_c {
private:
   template <typename F, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return sort_t<std::decay_t<F>, Ts...>{};
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

constexpr sort_c sort{};

HOLO_NS_END

#endif //GRAPH_SORT_H
