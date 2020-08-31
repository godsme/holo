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
      using type = type_list<T>;
   };

   template<typename ... Ts>
   struct flatten_impl {
      using type = decltype(( ... + typename flatten_trait<Ts>::type{}));
   };

   template<typename ... Ts>
   struct flatten_trait<type_list<Ts...>> {
      using type = typename flatten_impl<Ts...>::type;
   };
}

template<typename ... Ts>
using TL_flatten_t = typename type_list_detail::flatten_impl<Ts...>::type;

template<>
struct flatten_algo<type_list_tag> {
   template<typename ... Ts>
   constexpr static auto apply(type_list<Ts...>) -> TL_flatten_t<Ts...> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FLATTEN_H
