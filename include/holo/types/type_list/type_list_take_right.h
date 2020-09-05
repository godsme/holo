//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_TAKE_RIGHT_H
#define HOLO_TYPE_LIST_TAKE_RIGHT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_list/type_list_drop.h>

HOLO_NS_BEGIN

template<>
struct take_right_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>) -> TL_drop_t<sizeof...(Xs) - N, Xs...> {
      static_assert(N <= sizeof...(Xs));
      return {};
   }
};

template<>
struct last_algo<type_list_tag> {
   template<typename ... Xs>
   constexpr static auto apply(type_list<Xs...>) -> TL_drop_t<sizeof...(Xs) - 1, Xs...> {
      static_assert(sizeof...(Xs) > 0);
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_TAKE_RIGHT_H
