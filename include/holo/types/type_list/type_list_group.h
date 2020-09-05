//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_GROUP_H
#define HOLO_TYPE_LIST_GROUP_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_list/type_list_partition.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename F, typename R, typename ... Xs>
   struct group_impl {
      using type = R;
   };

   template<typename F, typename ... Rs, typename H, typename ... Xs>
   struct group_impl<F, type_list<Rs...>, H, Xs...> {
      constexpr static auto lt = [](auto elem){ return decltype(std::declval<F>()(elem, H{})){}; };
      using PRED = decltype(lt);
      using parts = TL_partition_t<PRED, Xs...>;
      using groups = type_list<Rs..., typename parts::first::template prepend_type<H>>;

      template<typename ... Ts>
      using group_more = typename group_impl<F, groups, Ts...>::type;

      using type = typename parts::second::template export_to<group_more>;
   };
}

template<typename F, typename ... Xs>
using TL_group_t = typename detail::group_impl<F, type_list<>, Xs...>::type;

template<>
struct group_by_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) -> TL_group_t<F, Xs...> { return {}; }
};

template<>
struct group_algo<type_list_tag> {
   template <typename ... Xs>
   constexpr static auto apply(type_list<Xs...> xs) {
      return group_by_algo<type_list_tag>::apply([](auto l, auto r) {
         return l == r;
      },
      xs);
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_GROUP_H
