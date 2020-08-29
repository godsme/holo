//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_FLATTEN_H
#define HOLO_TUPLE_FLATTEN_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct flatten_algo<tuple_tag> {
private:
   template<typename Xs, std::size_t ... Xn>
   constexpr static auto do_tuple_flatten(Xs const& xs, std::index_sequence<Xn...>) {
      return (tuple{} + ... + tuple_flatten(get<Xn>(xs)));
   }

   template<typename X>
   constexpr static auto tuple_flatten(X const& x) {
      if constexpr (Is_Tuple_v<X>) {
         return do_tuple_flatten(x, std::make_index_sequence<X::size>{});
      } else {
         return x;
      }
   }

public:
   template<typename ... Xs>
   constexpr static auto apply(tuple<Xs...> const& xs) {
      return tuple_flatten(xs);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_FLATTEN_H
