//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_TUPLE_H
#define GRAPH_TUPLE_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/type_c.h>
#include <holo/concept/algo.h>
#include <holo/algo/partial_apply.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

struct type_list_tag{};

namespace detail {
   template<template<typename ...> typename C, typename ... Ts>
   struct type_list_impl {};

   template<template<typename ...> typename C, typename H, typename ... Ts>
   struct type_list_impl<C, H, Ts...> {
      using head = H;
      using tail = C<Ts...>;
   };
}

template<typename ... Ts>
struct type_list : detail::type_list_impl<type_list, Ts...> {
   template<typename ... Xs>
   constexpr type_list(Xs&&...) {}

   using tag_type = type_list_tag;
   constexpr static size_t Size = sizeof...(Ts);

   template<typename T>
   using append_type = type_list<Ts..., T>;

   template<typename T>
   using prepend_type = type_list<T, Ts...>;

   template<template<typename ...> typename F>
   using export_to = F<Ts...>;

   template<typename ... Ts2>
   using append = type_list<Ts..., Ts2...>;

   template<typename TUPLE>
   using append_list = typename TUPLE::template export_to<append>;
};

template<typename ... Xs>
type_list(Xs&&...) -> type_list<std::decay_t<Xs>...>;

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator==(type_list<Ts1...> const& lhs, type_list<Ts2...> const& rhs) {
   return bool_c<std::is_same_v<type_list<Ts1...>, type_list<Ts2...>>>;
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator!=(type_list<Ts1...> const& lhs, type_list<Ts2...> const& rhs) {
   return !operator==(lhs, rhs);
}

template <typename ... Ts>
constexpr type_list<type_c_t <Ts>...> type_list_t{};

template<>
struct append_algo<type_list_tag> {
   template <typename T, typename ... Ts>
   constexpr static auto apply(T, type_list<Ts...>) {
      return type_list<Ts..., std::decay_t<T>>{};
   }
};

template<>
struct prepend_algo<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X, type_list<Xs...>) {
      return type_list<std::decay_t<X>, Xs...>{};
   }
};

template<>
struct concat_algo<type_list_tag> {
   template <typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>) {
      return type_list<Xs..., Ys...>{};
   }
};

template<>
struct contains_algo<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X, type_list<Xs...>) {
      return bool_c<(std::is_same_v<Xs, std::decay_t<X>> || ...)>;
   }
};

namespace detail {
   template<typename PRED, typename RESULT, typename = void, typename ... Ts>
   struct filter_impl {
      using type = RESULT;
   };

   template<typename PRED, typename ... Ys, typename H, typename ... Ts>
   struct filter_impl<PRED, type_list<Ys...>, std::enable_if_t<Is_Pred_Satisfied<PRED, H>>, H, Ts...> {
      using type = typename filter_impl<PRED, type_list<Ys..., H>, void, Ts...>::type;
   };

   template<typename PRED, typename RESULT, typename H, typename ... Ts>
   struct filter_impl<PRED, RESULT, std::enable_if_t<!Is_Pred_Satisfied <PRED, H>>, H, Ts...> {
   using type = typename filter_impl<PRED, RESULT, void, Ts...>::type;
};
}

template<typename F, typename ... Xs>
using TL_filter_t = typename detail::filter_impl<F, type_list<>, void, Xs...>::type;

template<>
struct filter_algo<type_list_tag> {
   template<typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) {
      return TL_filter_t<F, Xs...>{};
   }
};

HOLO_NS_END

#endif //GRAPH_TUPLE_H
