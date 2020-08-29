//
// Created by Darwin Yuan on 2020/8/28.
//

#ifndef HOLO_TUPLE_H
#define HOLO_TUPLE_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/tuple/tuple_contains.h>
#include <holo/types/tuple/tuple_concat.h>
#include <holo/types/tuple/tuple_prepend.h>
#include <holo/types/tuple/tuple_append.h>
#include <holo/types/tuple/tuple_filter.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename ... Xs, std::size_t ... Xn>
   constexpr auto take(tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      return tuple{get<Xn>(xs)...};
   }
}

template<std::size_t N, typename ... Xs, typename = std::enable_if_t<(sizeof...(Xs) >= N)>>
constexpr auto take(tuple<Xs...> const& xs) {
   if constexpr (sizeof...(Xs) == N) {
      return xs;
   } else if constexpr (N == 0) {
      return tuple{};
   } else {
      return detail::take(xs, std::make_index_sequence<N>{});
   }
}

namespace detail {
   template<std::size_t N, typename ... Xs, std::size_t ... Xn>
   constexpr auto drop(tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      return tuple{get<Xn+N>(xs)...};
   }
}

template<std::size_t N, typename ... Xs, typename = std::enable_if_t<(sizeof...(Xs) >= N)>>
constexpr auto drop(tuple<Xs...> const& xs) {
   if constexpr (sizeof...(Xs) == N) {
      return tuple{};
   } else {
      return detail::drop<N>(xs, std::make_index_sequence<sizeof...(Xs) - N>{});
   }
}

template<std::size_t N, typename ... Xs>
constexpr auto elem(tuple<Xs...> const& xs) {
   return get<N>(xs);
}

template<typename ... Xs>
constexpr auto head(tuple<Xs...> const& xs) {
   return get<0>(xs);
}

template<typename ... Xs>
constexpr auto tail(tuple<Xs...> const& xs) {
   return drop<1>(xs);
}

HOLO_NS_END

#endif //HOLO_TUPLE_H
