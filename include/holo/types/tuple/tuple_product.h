//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_PRODUCT_H
#define HOLO_TUPLE_PRODUCT_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/pair.h>

HOLO_NS_BEGIN

template<> struct product_algo<tuple_tag> {
private:
   template<typename X, typename Ys, std::size_t ... Yn>
   constexpr static auto product_2(X const& x, Ys const& ys, std::index_sequence<Yn...>) {
      return holo::make_tuple( pair{x, get<Yn>(ys)}... );
   }

   template<typename Xs, typename ... Ys, std::size_t ... Xn>
   constexpr static auto product(Xs const& xs, tuple<Ys...> const& ys, std::index_sequence<Xn...>) {
      return (product_2(get<Xn>(xs), ys, std::index_sequence_for<Ys...>{}) + ...);
   }

public:
   template<typename ... Xs, typename ... Ys>
   constexpr static auto apply(tuple<Xs...> const& xs, tuple<Ys...> const& ys) {
      return product(xs, ys, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_PRODUCT_H
