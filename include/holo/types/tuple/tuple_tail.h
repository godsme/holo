//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_TAIL_H
#define HOLO_TUPLE_TAIL_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/tuple/tuple_drop.h>

HOLO_NS_BEGIN

template<> struct tail_algo<tuple_tag> {
   template<typename Xs>
   constexpr static auto apply(Xs const& xs) {
      return drop_algo<tuple_tag>::apply(size_c<1>, xs);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_TAIL_H
