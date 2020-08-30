//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_PREPEND_H
#define HOLO_TUPLE_PREPEND_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct prepend_algo<tuple_tag> {
private:
   template<typename ... Xs, typename X, std::size_t ... Xn>
   constexpr static auto tuple_prepend(X const& x, tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      if constexpr (Is_Empty_Class<tuple<Xs...>>) {
         return holo::make_tuple(x, Xs{}...);
      } else {
         return holo::make_tuple(x, get<Xn>(xs)...);
      }
   }

public:
   template<typename ... Xs, typename X>
   constexpr static auto apply(X const& x, tuple<Xs...> const& xs) {
      if constexpr (Is_Empty_Class<tuple<Xs...>, X>) {
         return tuple<X, Xs...>{};
      } else {
         return tuple_prepend(x, xs, std::index_sequence_for<Xs...>{});
      }
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_PREPEND_H
