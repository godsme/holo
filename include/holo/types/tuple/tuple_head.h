//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_HEAD_H
#define HOLO_TUPLE_HEAD_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<> struct head_algo<tuple_tag> {
   template<typename ... Xs>
   constexpr static auto apply(tuple<Xs...> const& xs) {
      return get<0>(xs);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_HEAD_H
