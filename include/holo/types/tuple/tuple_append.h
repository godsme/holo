//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_APPEND_H
#define HOLO_TUPLE_APPEND_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct append_algo<tuple_tag> {
private:
   template<typename ... Xs, typename X, std::size_t ... Xn>
   constexpr static auto tuple_append(X const& x, tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      if constexpr (Is_Empty_Class<tuple<Xs...>>) {
         return tuple{Xs{}..., x};
      } else {
         return tuple{get<Xn>(xs)..., x};
      }
   }

public:
   template <typename X, typename ... Xs>
   constexpr static auto apply(X const& x, tuple<Xs...> const& xs) {
      if constexpr (Is_Empty_Class<tuple<Xs...>, X>) {
         return tuple<Xs..., X>{};
      } else {
         return tuple_append(x, xs, std::index_sequence_for<Xs...>{});
      }
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_APPEND_H
