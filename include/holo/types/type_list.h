//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_TUPLE_H
#define GRAPH_TUPLE_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/type_c.h>
#include <holo/concept/append.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

struct type_list_tag{};

template<typename ... Ts>
struct type_list {
   using tag_type = type_list_tag;

   constexpr static size_t Size = 0;

   template<typename T>
   using append_type = type_list<T>;

   template<typename T>
   using prepend_type = type_list<T>;

   template<template <typename ...> typename F>
   using export_to = F<>;

   template<typename ... Ts2>
   using append = type_list<Ts2...>;

   template<typename TUPLE>
   using append_list = TUPLE;
};

template<typename H, typename ... Ts>
struct type_list<H, Ts...> {
   using tag_type = type_list_tag;

   constexpr static size_t Size = sizeof...(Ts) + 1;
   using head = H;
   using tail = type_list<Ts...>;

   template<typename T>
   using append_type = type_list<H, Ts..., T>;

   template<typename T>
   using prepend_type = type_list<T, H, Ts...>;

   template<template <typename ...> typename F>
   using export_to = F<H, Ts...>;

   template<typename ... Ts2>
   using append = type_list<H, Ts..., Ts2...>;

   template<typename TUPLE>
   using append_list = typename TUPLE::template export_to<append>;
};

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator==(type_list<Ts1...> const& lhs, type_list<Ts2...> const& rhs) {
   return bool_c<std::is_same_v<type_list<Ts1...>, type_list<Ts2...>>>;
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator!=(type_list<Ts1...> const& lhs, type_list<Ts2...> const& rhs) {
   return !operator==(lhs, rhs);
}

template<typename ... Ts>
constexpr auto make_tuple(Ts&& ... args) {
   return type_list<std::decay_t<Ts>...>{};
}

template <typename ... Ts>
constexpr type_list<type_c_t < Ts>...> type_list_t{};

template<>
struct append_impl<type_list_tag> {
   template <typename T, typename ... Ts>
   constexpr static auto apply(T, type_list<Ts...>) {
      return type_list<Ts..., std::decay_t<T>>{};
   }
};

template<>
struct prepend_impl<type_list_tag> {
   template <typename X, typename ... Xs>
   constexpr static auto apply(X, type_list<Xs...>) {
      return type_list<std::decay_t<X>, Xs...>{};
   }
};

template<>
struct concat_impl<type_list_tag> {
   template <typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>) {
      return type_list<Xs..., Ys...>{};
   }
};

HOLO_NS_END

#endif //GRAPH_TUPLE_H
