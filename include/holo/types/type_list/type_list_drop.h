//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_DROP_H
#define HOLO_TYPE_LIST_DROP_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

namespace detail {
   template<std::size_t N, typename ... Xs>
   struct drop_impl;

   template<std::size_t N, typename H, typename ... Xs>
   struct drop_impl<N, H, Xs...> {
      using type = typename drop_impl<N-1, Xs...>::type;
   };

   template<typename ... Xs>
   struct drop_impl<0, Xs...> {
      using type = type_list<Xs...>;
   };
}

template<std::size_t N, typename ... Xs>
using TL_drop_t = typename detail::drop_impl<N, Xs...>::type;

template<>
struct drop_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>) -> TL_drop_t<N, Xs...> {
      static_assert(N <= sizeof...(Xs));
      return {};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_DROP_H
