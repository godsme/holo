//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_ELEM_H
#define HOLO_TUPLE_ELEM_H

#include <holo/types/tuple/tuple_t.h>

HOLO_NS_BEGIN

template<>
struct elem_algo<tuple_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, tuple<Xs...> const& xs) {
      return get<N>(xs);
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_ELEM_H
