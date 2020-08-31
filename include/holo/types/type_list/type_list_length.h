//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_TYPE_LIST_LENGTH_H
#define HOLO_TYPE_LIST_LENGTH_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

template<>
struct length_algo<type_list_tag> {
   template<typename Xs>
   constexpr static auto apply(Xs const&) -> size_c_t<Xs::Size> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_LENGTH_H
