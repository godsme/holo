//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FLATTEN_H
#define HOLO_TYPE_LIST_FLATTEN_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace {
   template <typename T>
   struct flatten_helper {
      constexpr flatten_helper(T value) : value_(value) {}
      using type = T;
      T value_;
   };

   template<typename ... Ts1, typename ... Ts2>
   constexpr auto operator+(flatten_helper<type_list<Ts1...>> acc, type_list<Ts2...> elem) {
      return flatten_helper{type_list<Ts1..., Ts2...>{}};
   }

   template<typename T>
   struct flatten_trait {
      using type = type_list<T>;
   };

   template<typename ... Ts>
   struct flatten_impl {
      using type = typename decltype((flatten_helper<type_list<>>{type_list<>{}} + ... + typename flatten_trait<Ts>::type{}))::type;
   };

   template<typename ... Ts>
   struct flatten_trait<type_list<Ts...>> {
      using type = typename flatten_impl<Ts...>::type;
   };
}

template<typename ... Ts>
using TL_flatten_t = typename flatten_impl<Ts...>::type;

template<>
struct flatten_algo<type_list_tag> {
   template<typename ... Ts>
   constexpr static auto apply(type_list<Ts...>) {
      return TL_flatten_t<Ts...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FLATTEN_H
