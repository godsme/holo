//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FLATTEN_H
#define HOLO_TYPE_LIST_FLATTEN_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace type_list_detail {
   template<typename T>
   struct flatten_trait {
      constexpr static auto value = type_list<T>{};
   };

   template<typename ... Ts>
   struct flatten_impl {
      constexpr static auto value = ( ... + flatten_trait<Ts>::value);
   };

   template<typename ... Ts>
   struct flatten_trait<type_list<Ts...>> {
      constexpr static auto value = flatten_impl<Ts...>::value;
   };
}

template<typename ... Ts>
constexpr auto TL_flatten_v = type_list_detail::flatten_impl<Ts...>::value;

template<>
struct flatten_algo<type_list_tag> {
   template<typename ... Ts>
   constexpr static auto apply(type_list<Ts...>) { return TL_flatten_v<Ts...>; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FLATTEN_H
