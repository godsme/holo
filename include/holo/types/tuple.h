//
// Created by Darwin Yuan on 2020/8/28.
//

#ifndef HOLO_TUPLE_H
#define HOLO_TUPLE_H

#include <holo/types/integral_c.h>
#include <holo/types/detail/ebo.h>
#include <utility>

HOLO_NS_BEGIN

namespace detail {
   template<typename Indices, typename ... Xs>
   struct tuple_impl;

   template<std::size_t ... I, typename ... Xs>
   struct tuple_impl<std::index_sequence<I...>, Xs...> : ebo<I, Xs>... {
      constexpr static std::size_t size = sizeof...(Xs);

      constexpr tuple_impl() = default;
      constexpr tuple_impl(tuple_impl const& rhs) = default;
      template<typename ... Ys>
      constexpr tuple_impl(Ys const& ... args)
         : ebo<I, Xs>{static_cast<Xs const&>(args)}... {}
   };
}

template<typename ... Xs>
struct tuple : detail::tuple_impl<std::index_sequence_for<Xs...>, Xs...> {
   using base = detail::tuple_impl<std::index_sequence_for<Xs...>, Xs...>;
   using base::base;
};

template<typename ... Xs>
tuple(Xs const& ...) -> tuple<Xs...>;

template<std::size_t N, typename ... Xs>
constexpr auto get(tuple<Xs...> const& xs) noexcept -> decltype(auto) {
   return detail::ebo_get<N>(xs);
}

namespace detail {
   template<std::size_t ... I, typename Xs, typename Ys>
   constexpr auto tuple_equals(Xs const& xs, Ys const& ys) noexcept {
      return bool_c<((get<I>(xs) == get<I>(ys)) && ...)>;
   }
}

template<typename ... Xs, typename ... Ys>
constexpr auto operator==(tuple<Xs...> const& lhs, tuple<Ys...> const& rhs) noexcept {
   if constexpr (std::is_same_v<tuple<Xs...>, tuple<Ys...>>) {
      return detail::tuple_equals(lhs, rhs);
   } else {
      return bool_c<false>;
   }
}

template<typename ... Xs, typename ... Ys>
constexpr auto operator!=(tuple<Xs...> const& lhs, tuple<Ys...> const& rhs) noexcept {
   return !operator==(lhs, rhs);
}

HOLO_NS_END

#endif //HOLO_TUPLE_H
