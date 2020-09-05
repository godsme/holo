//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_EMPTY_H
#define HOLO_TYPE_LIST_EMPTY_H

#include <holo/types/type_list/type_list_t.h>

HOLO_NS_BEGIN

template<>
struct empty_algo<type_list_tag> {
   template<typename ... Xs>
   constexpr static auto apply(type_list<Xs...>) {
      return bool_c<sizeof...(Xs) == 0>;
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_EMPTY_H
