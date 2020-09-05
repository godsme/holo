//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_T_H
#define HOLO_TYPE_LIST_T_H

#include <holo/types/type_c.h>
#include <holo/types/integral_constant/size_c.h>
#include <holo/concept/algo.h>
#include <holo/types/tuple_trait.h>
#include <type_traits>

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
   using tag_type = type_list_tag;
   constexpr static std::size_t Size = sizeof...(Ts);

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

template<typename ... Ts>
constexpr auto make_type_list(Ts&& ...) -> type_list<std::decay_t<Ts>...> {
    return {};
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator==(type_list<Ts1...>, type_list<Ts2...>) {
   return bool_c<std::is_same_v<type_list<Ts1...>, type_list<Ts2...>>>;
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator!=(type_list<Ts1...> lhs, type_list<Ts2...> rhs) {
   return !operator==(lhs, rhs);
}

template <typename ... Ts>
constexpr type_list<type_c_t <Ts>...> type_list_t{};

template <template<typename ...> typename C, typename ... Ts>
struct tuple_trait<type_list<Ts...>, C> {
   using type = C<typename Ts::type...>;
};

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator+(type_list<Ts1...>, type_list<Ts2...>) {
   return type_list<Ts1..., Ts2...>{};
}

template<typename T>
struct is_type_list : false_type {};

template<typename ... Ts>
struct is_type_list<type_list<Ts...>> : true_type {};

template<typename T>
constexpr bool is_type_list_v = is_type_list<T>::value();

template<typename ... Ts, typename T, typename = std::enable_if_t<!is_type_list_v<T>>>
constexpr auto operator+(type_list<Ts...>, T) {
   return type_list<Ts..., T>{};
}

template<typename T>
constexpr auto sizeof_type(type_c_t<T>) -> size_c_t<sizeof(T)> {
   return {};
}

template <bool ... Vs>
constexpr type_list<bool_c_t<Vs>...> bool_list_t{};

template <std::size_t ... Vs>
constexpr type_list<size_c_t<Vs>...> size_list_t{};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_T_H
