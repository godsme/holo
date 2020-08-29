//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_T_H
#define HOLO_TYPE_LIST_T_H

#include <holo/types/type_c.h>
#include <holo/concept/algo.h>
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
constexpr auto operator==(type_list<Ts1...> const&, type_list<Ts2...> const&) {
   return bool_c<std::is_same_v<type_list<Ts1...>, type_list<Ts2...>>>;
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto operator!=(type_list<Ts1...> const& lhs, type_list<Ts2...> const& rhs) {
   return !operator==(lhs, rhs);
}

template <typename ... Ts>
constexpr type_list<type_c_t <Ts>...> type_list_t{};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_T_H
