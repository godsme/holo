//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef GRAPH_FOLD_LEFT_H
#define GRAPH_FOLD_LEFT_H

#include <holo/holo_ns.h>
#include <holo/types/type_c.h>
#include <holo/types/tuple.h>
#include <type_traits>
#include <tuple>

HOLO_NS_BEGIN

namespace detail {
   template <typename T, typename F>
   struct fold_helper {
      constexpr fold_helper(T value, F f) : value_(value), f_(f) {}
      T value_;
      F f_;
   };

   template<typename T, typename F, typename ELEM>
   constexpr auto operator<<(fold_helper<T, F> acc, ELEM elem) {
      return fold_helper{acc.f_(acc.value_, elem), acc.f_};
   }
}

template <typename ...Ts, typename INIT, typename F>
constexpr auto fold_left(INIT&& init, F&& f, const tuple<Ts...>& tuple) {
   auto result = (detail::fold_helper{std::forward<INIT>(init), std::forward<F>(f)} <<  ... << Ts{});
   return result.value_;
}

HOLO_NS_END

#endif //GRAPH_FOLD_LEFT_H
