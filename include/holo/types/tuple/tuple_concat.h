//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_CONCAT_H
#define HOLO_TUPLE_CONCAT_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct concat_algo<tuple_tag> {
   template<typename ... Xs, typename ... Ys>
   constexpr static auto apply(tuple<Xs...> const& xs, tuple<Ys...> const& ys) {
      return tuple_cat(xs, ys);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_CONCAT_H
