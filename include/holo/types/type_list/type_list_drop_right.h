//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_DROP_RIGHT_H
#define HOLO_TYPE_LIST_DROP_RIGHT_H

#include <holo/types/type_list/type_list_take.h>

HOLO_NS_BEGIN

template<>
struct drop_right_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>)
   -> TL_take_t<sizeof...(Xs) - N, Xs...> {
      static_assert(N <= sizeof...(Xs));
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_DROP_RIGHT_H
