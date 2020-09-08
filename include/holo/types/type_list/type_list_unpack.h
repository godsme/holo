//
// Created by Darwin Yuan on 2020/9/8.
//

#ifndef HOLO_TYPE_LIST_UNPACK_H
#define HOLO_TYPE_LIST_UNPACK_H

#include <holo/types/type_list/type_list_t.h>

HOLO_NS_BEGIN

template<> struct unpack_algo<type_list_tag> {
   template<typename F, typename ... Ts>
   constexpr static auto apply(F&& f, type_list<Ts...>) {
      return f(Ts{}...);
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_UNPACK_H
