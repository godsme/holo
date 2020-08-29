//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_CONTAINS_H
#define HOLO_TUPLE_CONTAINS_H

#include <holo/types/tuple/tuple.h>
#include <holo/types/non_comparable.h>

HOLO_NS_BEGIN

template<>
struct contains_algo<tuple_tag> {
private:
   template<typename X, typename ... Xs, std::size_t ... Xn>
   constexpr static auto tuple_contains(X const& x, tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      return (std::is_same_v<decltype(get<Xn>(xs) == x), true_type> || ...);
   }

public:
   template<typename X, typename ... Xs>
   constexpr static auto apply(X const& x, tuple<Xs...> const& xs) {
      return tuple_contains(x, xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_CONTAINS_H
