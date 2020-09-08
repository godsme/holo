//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_TAKE_H
#define HOLO_TUPLE_TAKE_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct take_algo<tuple_tag> {
private:
   template<typename ... Xs, std::size_t ... Xn>
   constexpr static auto tuple_take(tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      return holo::make_tuple(get<Xn>(xs)...);
   }

public:
   template<std::size_t N, typename ... Xs, typename = std::enable_if_t<(sizeof...(Xs) >= N)>>
   constexpr static auto apply(size_c_t<N>, tuple<Xs...> const& xs) {
      return tuple_take(xs, std::make_index_sequence<N>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_TAKE_H
