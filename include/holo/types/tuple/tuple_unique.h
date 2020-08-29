//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_UNIQUE_H
#define HOLO_TUPLE_UNIQUE_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/detail/filter_result.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace tuple_detail {
   template<typename H, typename RESULT>
   constexpr bool Contains = std::is_same_v<bool_c_t<true>, decltype(contains(std::declval<H>(), RESULT{}))>;

   template<typename RESULT, std::size_t N, typename ... Ts>
      struct unique_impl {
         using type = RESULT;
      };

      template<std::size_t ... Xn, std::size_t N, typename H, typename ... Ts>
      struct unique_impl<std::index_sequence<Xn...>, N, H, Ts...> {
      using type = std::conditional_t<
         true,
         typename unique_impl<std::index_sequence<Xn...>, N+1, Ts...>::type,
         typename unique_impl<std::index_sequence<Xn..., N>, N+1, Ts...>::type>;
   };
}

template<> struct unique_algo<tuple_tag> {
private:
public:
   template<typename ... Xs>
   constexpr static auto apply(tuple<Xs...> const& xs) {
      return tuple_transform(xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_UNIQUE_H
