//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_ELEM_H
#define HOLO_TYPE_LIST_ELEM_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

namespace detail {
   template<std::size_t N, typename ... Xs>
   struct elem_impl;

   template<std::size_t N, typename H, typename ... Xs>
   struct elem_impl<N, H, Xs...> {
      using type = typename elem_impl<N-1, Xs...>::type;
   };

   template<typename H, typename ... Xs>
   struct elem_impl<0, H, Xs...> {
      using type = H;
   };
}

template<>
struct elem_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>) {
      static_assert(N < sizeof...(Xs));
      return typename detail::elem_impl<N, Xs...>::type{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_ELEM_H
