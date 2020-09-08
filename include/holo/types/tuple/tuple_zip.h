//
// Created by Darwin Yuan on 2020/9/8.
//

#ifndef HOLO_TUPLE_ZIP_H
#define HOLO_TUPLE_ZIP_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/tuple/pair.h>

HOLO_NS_BEGIN

template<> struct zip_algo<tuple_tag> {
private:
   template<typename Xs, typename Ys, std::size_t ... Xn>
   constexpr static auto make(Xs const& xs, Ys const& ys, std::index_sequence<Xn...>) {
      return holo::make_tuple(holo::make_value_pair(holo::get<Xn>(xs), holo::get<Xn>(ys))...);
   }

public:
   template<typename ... Xs, typename ... Ys>
   constexpr static auto apply(tuple<Xs...> const& xs, tuple<Ys...> const& ys) {
      static_assert(sizeof...(Xs) == sizeof...(Ys));
      return make(xs, ys, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_ZIP_H
