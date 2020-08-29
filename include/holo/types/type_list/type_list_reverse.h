//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_REVERSE_H
#define HOLO_TYPE_LIST_REVERSE_H

#include <holo/types/type_list/type_list_t.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename RESULT, typename ... Ts>
   struct reverse_impl {
      using type = RESULT;
   };

   template<typename ... Xs, typename H, typename ... Ts>
   struct reverse_impl<type_list<Xs...>, H, Ts...> {
      using type = typename reverse_impl<type_list<H, Xs...>, Ts...>::type;
   };
}

template<typename ... Ts>
using TL_reverse_t = typename detail::reverse_impl<type_list<>, Ts...>::type;

template<> struct reverse_algo<type_list_tag> {
   template<typename ... Ts>
   constexpr static auto apply(type_list<Ts...>) {
      return TL_reverse_t<Ts...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_REVERSE_H
