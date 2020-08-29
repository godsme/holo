//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_CONTAINS_H
#define HOLO_TUPLE_CONTAINS_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/non_comparable.h>

HOLO_NS_BEGIN

template<>
struct contains_algo<tuple_tag> {
private:
   template<typename X, typename ... Xs, std::size_t ... Xn>
   constexpr static auto tuple_contains(X const& x, tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      static_assert((Is_Integral_Const_V<decltype(get<Xn>(xs) == x)> || ...), "'==' should return an integral constant");
      return (Is_True_V<decltype(get<Xn>(xs) == x)> || ...);
   }

public:
   template<typename X, typename ... Xs>
   constexpr static auto apply(X const& x, tuple<Xs...> const& xs) {
      return tuple_contains(x, xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_CONTAINS_H
