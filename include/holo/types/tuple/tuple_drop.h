//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_DROP_H
#define HOLO_TUPLE_DROP_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct drop_algo<tuple_tag> {
private:
   template<std::size_t N, typename ... Xs, std::size_t ... Xn>
   constexpr static auto tuple_drop(tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      return holo::make_tuple(get<Xn+N>(xs)...);
   }

public:
   template<std::size_t N, typename ... Xs, typename = std::enable_if_t<(sizeof...(Xs) >= N)>>
   constexpr static auto apply(size_c_t<N>, tuple<Xs...> const& xs) {
      return tuple_drop<N>(xs, std::make_index_sequence<sizeof...(Xs) - N>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_DROP_H
