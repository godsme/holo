//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_T_H
#define HOLO_TUPLE_T_H

#include <holo/types/integral_c.h>
#include <holo/types/detail/ebo.h>
#include <holo/types/size_c.h>
#include <holo/concept/algo.h>
#include <utility>

HOLO_NS_BEGIN

struct tuple_tag {};

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
   using tag_type = tuple_tag;
   using base = detail::tuple_impl<std::index_sequence_for<Xs...>, Xs...>;
   using base::base;
};

template<typename ... Xs>
tuple(Xs&& ...) -> tuple<std::decay_t<Xs>...>;

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
      return false_c;
   }
}

template<typename ... Xs, typename ... Ys>
constexpr auto operator!=(tuple<Xs...> const& lhs, tuple<Ys...> const& rhs) noexcept {
   return !operator==(lhs, rhs);
}

template<std::size_t I, typename Xs>
using tuple_element = std::decay_t<decltype(detail::ebo_get<I>(std::declval<Xs>()))>;

template<typename ... Xs>
constexpr auto tuple_size(tuple<Xs...> const& lhs) {
   return size_c<sizeof...(Xs)>;
}

template<typename ... Ts>
constexpr bool Is_Empty_Class = (std::is_empty_v<Ts> && ...);

namespace detail {
   template<typename ... Xs, typename ... Ys, std::size_t ... Xn, std::size_t ... Yn>
   constexpr auto tuple_cat(tuple<Xs...> const& xs, tuple<Ys...> const& ys, std::index_sequence<Xn...>, std::index_sequence<Yn...>) {
      if constexpr (Is_Empty_Class<tuple<Xs...>>) {
         return tuple<Xs..., Ys...>{Xs{}..., get<Yn>(ys)...};
      } else if constexpr (Is_Empty_Class<tuple<Ys...>>) {
         return tuple<Xs..., Ys...>{get<Xn>(xs)..., Ys{}...};
      } else {
         return tuple<Xs..., Ys...>{get<Xn>(xs)..., get<Yn>(ys)...};
      }
   }
}

template<typename ... Xs, typename ... Ys>
constexpr auto tuple_cat(tuple<Xs...> const& xs, tuple<Ys...> const& ys) {
   if constexpr (Is_Empty_Class<tuple<Xs...>, tuple<Ys...>>) {
      return tuple<Xs..., Ys...>{};
   } else {
      return detail::tuple_cat(xs, ys,
                               std::index_sequence_for<Xs...>{},
                               std::index_sequence_for<Ys...>{});
   }
}

HOLO_NS_END

#endif //HOLO_TUPLE_T_H
