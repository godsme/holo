//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_SORT_H
#define HOLO_TYPE_LIST_SORT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_list/type_list_partition.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename LT, typename ... Ts>
   struct sort_impl {
      using type = type_list<>;
   };

   template<typename LT, typename H, typename ... Ts>
   struct sort_impl<LT, H, Ts...> {
      constexpr static auto lt = [](auto elem){ return decltype(std::declval<LT>()(elem, H{})){}; };
      using PRED = decltype(lt);
      template<typename ... TS> using sort_more = typename sort_impl<LT, TS...>::type;
      using parts = TL_partition_t<PRED, Ts...>;
      using lesser  = typename parts::first::template export_to<sort_more>;
      using greater = typename parts::second::template export_to<sort_more>;
      using type = typename lesser::template append_type<H>::template append_list<greater>;
   };
}

template<typename LT, typename ... Ts>
using TL_sort_t = typename detail::sort_impl<LT, Ts...>::type;

template<> struct sort_algo<type_list_tag> {
   template<typename F, typename ... Ts>
   constexpr static auto apply(F, type_list<Ts...>) {
      return TL_sort_t<std::decay_t<F>, Ts...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_SORT_H
