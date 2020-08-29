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
   template<typename H, typename TUPLE, std::size_t ... Xn>
   constexpr bool Contains = (Is_True_V<decltype(get<Xn>(std::declval<TUPLE>()) == std::declval<H>())> || ...);

   template<typename TUPLE, typename RESULT, std::size_t N, typename ... Ts>
      struct unique_impl {
         using type = RESULT;
      };

      template<typename TUPLE, std::size_t ... Xn, std::size_t N, typename H, typename ... Ts>
      struct unique_impl<TUPLE, std::index_sequence<Xn...>, N, H, Ts...> {
      using type = std::conditional_t<
         Contains<H, TUPLE, Xn...>,
         typename unique_impl<TUPLE, std::index_sequence<Xn...>, N+1, Ts...>::type,
         typename unique_impl<TUPLE, std::index_sequence<Xn..., N>, N+1, Ts...>::type>;
   };
}

template<> struct unique_algo<tuple_tag> {
private:
   template<typename  Xs, std::size_t ... Xn>
   constexpr static auto tuple_unique(Xs const& xs, std::index_sequence<Xn...>) {
      return tuple{get<Xn>(xs)...};
   }
public:
   template<typename ... Xs>
   constexpr static auto apply(tuple<Xs...> const& xs) {
      using indices = typename tuple_detail::unique_impl<tuple<Xs...>, std::index_sequence<>, 0, Xs...>::type;
      return tuple_unique(xs, indices{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_UNIQUE_H
