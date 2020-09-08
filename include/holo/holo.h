//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_HOLO_H
#define HOLO_HOLO_H

#include <holo/types/type_list/type_list.h>
#include <holo/types/tuple/tuple.h>
#include <holo/types/tuple/pair.h>
#include <holo/types/integral_constant/char_c.h>
#include <holo/types/type_transform.h>
#include <holo/algo/tail.h>
#include <holo/algo/fold_left.h>
#include <holo/algo/take.h>
#include <holo/algo/drop.h>
#include <holo/algo/append.h>
#include <holo/algo/prepend.h>
#include <holo/algo/find_if.h>
#include <holo/algo/transform.h>
#include <holo/algo/filter.h>
#include <holo/algo/contains.h>
#include <holo/algo/concat.h>
#include <holo/algo/remove_if.h>
#include <holo/algo/reverse.h>
#include <holo/algo/head.h>
#include <holo/algo/partition.h>
#include <holo/algo/sort.h>
#include <holo/types/integral_constant/sizeof_c.h>
#include <holo/algo/unique.h>
#include <holo/algo/flatten.h>
#include <holo/algo/product.h>
#include <holo/algo/first.h>
#include <holo/algo/second.h>
#include <holo/algo/length.h>
#include <holo/algo/zip.h>
#include <holo/algo/empty.h>
#include <holo/algo/group.h>
#include <holo/algo/any_of.h>
#include <holo/algo/all_of.h>
#include <holo/algo/none_of.h>
#include <holo/algo/take_right.h>
#include <holo/algo/drop_right.h>
#include <holo/algo/last.h>


HOLO_NS_BEGIN

template<typename ... Xs>
constexpr auto make_list(Xs&& ... xs) {
   if constexpr (sizeof...(Xs) == 0) {
      return holo::type_list_t<>;
   } if constexpr ((std::is_empty_v<std::decay_t<Xs>> && ...)) {
      return holo::type_list<std::decay_t<Xs>...>{};
   } else {
      static_assert((std::is_empty_v<std::decay_t<Xs>> && ...));
      return holo::make_tuple(std::forward<Xs>(xs)...);
   }
}

template<typename X, typename Y>
constexpr auto make_pair(X&& x, Y&& y) {
   if constexpr ((std::is_empty_v<std::decay_t<X>> && std::is_empty_v<std::decay_t<Y>>)) {
      return holo::type_pair<std::decay_t<X>, std::decay_t<Y>>{};
   } else {
      return holo::make_value_pair(std::forward<X>(x), std::forward<Y>(y));
   }
}

template<typename ... Xs>
constexpr auto list_t = type_list_t<Xs...>;

template<typename X, typename Y>
constexpr auto pair_t = type_pair_t<X, Y>;

HOLO_NS_END


#endif //HOLO_HOLO_H
