//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_REVERSE_H
#define HOLO_TUPLE_REVERSE_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct reverse_algo<tuple_tag> {
private:
   template<typename Xs, std::size_t ... Xn>
   constexpr static auto tuple_reverse(Xs const& xs, std::index_sequence<Xn...>) {
      return tuple{get<sizeof...(Xn) - 1 - Xn>(xs)...};
   }

public:
   template<typename ... Xs>
   constexpr static auto apply(tuple<Xs...> const& xs) {
      return tuple_reverse(xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_REVERSE_H
