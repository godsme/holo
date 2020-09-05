//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_SPLIT_H
#define HOLO_TYPE_LIST_SPLIT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_list/type_pair.h>

HOLO_NS_BEGIN

namespace detail {
   template<std::size_t N, typename R, typename ... Xs>
   struct split_impl;

   template<std::size_t N, typename ... Rs, typename H, typename ... Xs>
   struct split_impl<N, type_list<Rs...>, H, Xs...> {
      using type = typename split_impl<N-1, type_list<Rs..., H>, Xs...>::type;
   };

   template<typename R, typename ... Xs>
   struct split_impl<0, R, Xs...> {
      using type = type_pair<R, type_list<Xs...>>;
   };
}

template<std::size_t N, typename ... Xs>
using TL_split_t = typename detail::split_impl<N, type_list<>, Xs...>::type;

template<>
struct split_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>) -> TL_split_t<N, Xs...> {
      static_assert(N <= sizeof...(Xs));
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_SPLIT_H
