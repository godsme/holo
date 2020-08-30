//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_TRANSFORM_H
#define HOLO_TUPLE_TRANSFORM_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/detail/filter_result.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<> struct transform_algo<tuple_tag> {
private:
   template<typename F, typename Xs, std::size_t ... Xn>
   constexpr static auto tuple_transform(F const& f, Xs const& xs, std::index_sequence<Xn...>) {
      return holo::make_tuple(f(get<Xn>(xs))...);
   }

public:
   template<typename F, typename ... Xs>
   constexpr static auto apply(F const& f, tuple<Xs...> const& xs) {
      return tuple_transform(f, xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_TRANSFORM_H
