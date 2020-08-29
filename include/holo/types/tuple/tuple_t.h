//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_T_H
#define HOLO_TUPLE_T_H

#include <holo/types/type_c.h>
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

// must be final
template<typename ... Xs>
struct tuple final : detail::tuple_impl<std::index_sequence_for<Xs...>, Xs...> {
   using tag_type = tuple_tag;
   using base = detail::tuple_impl<std::index_sequence_for<Xs...>, Xs...>;
   using base::base;
};

template<typename ... Xs>
tuple(Xs&& ...) -> tuple<std::decay_t<Xs>...>;

template<typename ... Xs>
constexpr tuple<type_c_t<Xs>...> tuple_t{};

template<typename T>
struct Is_Tuple : false_type {};

template<typename ... Xs>
struct Is_Tuple<tuple<Xs...>> : true_type {};

template<typename T>
constexpr bool Is_Tuple_v = Is_Tuple<std::decay_t<T>>::value();

template<typename T>
constexpr bool is_tuple(T const&) {
   return bool_c<Is_Tuple_v<T>>;
}

template<std::size_t N, typename Xs>
constexpr auto get(Xs const& xs) noexcept -> decltype(auto) {
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
using tuple_element_t = std::decay_t<decltype(detail::ebo_get<I>(std::declval<Xs>()))>;

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

namespace detail {
   template<typename ... Xs, typename X, std::size_t ... Xn>
   constexpr auto tuple_append(X const& x, tuple<Xs...> const& xs, std::index_sequence<Xn...>) {
      if constexpr (Is_Empty_Class<tuple<Xs...>>) {
         return tuple{Xs{}..., x};
      } else {
         return tuple{get<Xn>(xs)..., x};
      }
   }
}

template <typename X, typename ... Xs>
constexpr static auto tuple_append(X const& x, tuple<Xs...> const& xs) {
   if constexpr (Is_Empty_Class<tuple<Xs...>, X>) {
      return tuple<Xs..., X>{};
   } else {
      return detail::tuple_append(x, xs, std::index_sequence_for<Xs...>{});
   }
}

template<typename ... Xs, typename ... Ys>
constexpr auto operator+(tuple<Xs...> const& xs, tuple<Ys...> const& ys) {
   return tuple_cat(xs, ys);
}

template<typename ... Xs, typename X>
constexpr auto operator+(tuple<Xs...> const& xs, X const& x) {
   return tuple_append(x, xs);
}

HOLO_NS_END

#endif //HOLO_TUPLE_T_H
