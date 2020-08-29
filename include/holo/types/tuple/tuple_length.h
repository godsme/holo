//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_TUPLE_LENGTH_H
#define HOLO_TUPLE_LENGTH_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct length_algo<tuple_tag> {
   template<typename Xs>
   constexpr static auto apply(Xs const&) -> size_c_t<Xs::Size> {
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_LENGTH_H
