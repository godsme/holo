//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_UNIQUE_H
#define HOLO_TYPE_LIST_UNIQUE_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/algo/contains.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename RESULT, typename ... Ts>
   struct unique_impl {
      using type = RESULT;
   };

   template<typename ... Xs, typename H, typename ... Ts>
   struct unique_impl<type_list<Xs...>, H, Ts...> {
      using type = std::conditional_t<
         Contains<H, type_list<Xs...>>,
         typename unique_impl<type_list<Xs...>, Ts...>::type,
         typename unique_impl<type_list<Xs..., H>, Ts...>::type>;
   };
}

template<typename ... Ts>
using TL_unique_t = typename detail::unique_impl<type_list<>, Ts...>::type;

template<> struct unique_algo<type_list_tag> {
   template<typename ... Ts>
   constexpr static auto apply(type_list<Ts...>) {
      return TL_unique_t<Ts...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_UNIQUE_H
