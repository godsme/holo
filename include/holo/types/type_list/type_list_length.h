//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_TYPE_LIST_LENGTH_H
#define HOLO_TYPE_LIST_LENGTH_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/integral_constant/size_c.h>

HOLO_NS_BEGIN

template<>
struct length_algo<type_list_tag> {
   template<typename ... Xs>
   constexpr static auto apply(type_list<Xs...>) -> size_c_t<sizeof...(Xs)> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_LENGTH_H
