//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_APPEND_H
#define HOLO_TUPLE_APPEND_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct append_algo<tuple_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X const& x, tuple<Xs...> const& xs) {
      return tuple_append(x, xs);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_APPEND_H
