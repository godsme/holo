//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_TUPLE_H
#define GRAPH_TUPLE_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/type_c.h>

HOLO_NS_BEGIN

template<typename ... Ts>
struct tuple {
   constexpr static size_t Size = 0;

   template<typename T>
   using append_type = tuple<T>;

   template<typename T>
   using prepend_type = tuple<T>;

   template<template <typename ...> typename F>
   using export_to = F<>;

   template<typename ... Ts2>
   using append = tuple<Ts2...>;

   template<typename TUPLE>
   using append_list = TUPLE;
};

template<typename H, typename ... Ts>
struct tuple<H, Ts...> {
   constexpr static size_t Size = sizeof...(Ts) + 1;
   using head = H;
   using tail = tuple<Ts...>;

   template<typename T>
   using append_type = tuple<H, Ts..., T>;

   template<typename T>
   using prepend_type = tuple<T, H, Ts...>;

   template<template <typename ...> typename F>
   using export_to = F<H, Ts...>;

   template<typename ... Ts2>
   using append = tuple<H, Ts..., Ts2...>;

   template<typename TUPLE>
   using append_list = typename TUPLE::template export_to<append>;
};

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator==(tuple<Ts1...> const& lhs, tuple<Ts2...> const& rhs) {
   return bool_c<std::is_same_v<tuple<Ts1...>, tuple<Ts2...>>>;
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator!=(tuple<Ts1...> const& lhs, tuple<Ts2...> const& rhs) {
   return !operator==(lhs, rhs);
}

template<typename ... Ts>
constexpr auto make_tuple(Ts&& ... args) {
   return tuple<std::decay_t<Ts>...>{};
}

template <typename ... Ts>
constexpr tuple<type_c_t<Ts>...> tuple_t{};

template<typename T>
struct tuple_size;

template<typename ... Ts>
struct tuple_size<tuple<Ts...>> {
   constexpr static size_t value = sizeof...(Ts);
};

template<typename T>
constexpr size_t tuple_size_v = tuple_size<T>::value;

template<typename ...Ts1, typename ...Ts2>
constexpr auto tuple_cat(const tuple<Ts1...>&, const tuple<Ts2...>&) {
   return tuple<Ts1..., Ts2...>{};
}

HOLO_NS_END

#endif //GRAPH_TUPLE_H
