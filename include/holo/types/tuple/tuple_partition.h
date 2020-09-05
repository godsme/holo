//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_PARTITION_H
#define HOLO_TUPLE_PARTITION_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/tuple/pair.h>

HOLO_NS_BEGIN

namespace tuple_detail {
   template<typename PRED, typename FIRST, typename SECOND, std::size_t N, typename ... Ts>
   struct partition_impl {
      using type = struct {
         using first = FIRST;
         using second = SECOND;
      };
   };

   template<typename PRED, std::size_t ... Xn, std::size_t ... Yn, std::size_t N, typename H, typename ... Ts>
   struct partition_impl<PRED, std::index_sequence<Xn...>, std::index_sequence<Yn...>, N, H, Ts...> {
      using type = std::conditional_t<
         HOLO_NS::detail::Is_Pred_Satisfied<PRED, H>,
         typename partition_impl<PRED, std::index_sequence<Xn..., N>, std::index_sequence<Yn...>, N+1, Ts...>::type,
         typename partition_impl<PRED, std::index_sequence<Xn...>, std::index_sequence<Yn..., N>, N+1, Ts...>::type>;
   };
}

template<typename F, typename ... Xs>
using tuple_partition_t = typename tuple_detail::partition_impl<F, std::index_sequence<>, std::index_sequence<>, 0, Xs...>::type;

template<> struct partition_algo<tuple_tag> {
private:
   template<typename Xs, std::size_t ... Xn>
   constexpr static auto select(Xs const& xs, std::index_sequence<Xn...>) {
      return holo::make_tuple(get<Xn>(xs)...);
   }

public:
   template<typename F, typename ... Xs>
   constexpr static auto apply(F&&, tuple<Xs...> const& xs) {
      using first  = typename tuple_partition_t<F, Xs...>::first;
      using second = typename tuple_partition_t<F, Xs...>::second;
      return pair{select(xs, first{}), select(xs, second{})};
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_PARTITION_H
