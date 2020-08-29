//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_PRODUCT_H
#define HOLO_TYPE_LIST_PRODUCT_H

#include <holo/types/type_list/type_list.h>
#include <holo/types/type_pair.h>
#include <holo/types/type_list/type_list_flatten.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename T, typename ... Ts>
   using product_impl = type_list<type_pair<T, Ts> ...>;
}

template<>
struct product_algo<type_list_tag> {
   template <typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>) {
      return TL_flatten_t<detail::product_impl<Xs, Ys...> ...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_PRODUCT_H
