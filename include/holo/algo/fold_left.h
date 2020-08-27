//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef GRAPH_FOLD_LEFT_H
#define GRAPH_FOLD_LEFT_H

#include <holo/holo_ns.h>
#include <holo/types/type_c.h>
#include <holo/types/tuple.h>
#include <type_traits>

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


struct fold_left_c {
private:
   template <typename ...Ts, typename INIT, typename F>
   constexpr static auto invoke(INIT init, F f, tuple<Ts...>) {
      auto result = (detail::fold_helper{init, f} <<  ... << Ts{});
      return result.value_;
   }

public:
   template <typename ...Ts, typename INIT, typename F>
   constexpr auto operator()(INIT&& init, F&& f, tuple<Ts...> const& stream) const {
      return invoke(init, f, stream);
   }

   template <typename INIT, typename F>
   constexpr auto operator()(INIT&& init, F&& f) const {
      return [=](auto stream) { return invoke(init, f, stream); };
   }
};

constexpr fold_left_c fold_left{};

HOLO_NS_END

#endif //GRAPH_FOLD_LEFT_H
