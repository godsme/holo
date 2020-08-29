//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_TRANSFORM_H
#define HOLO_TYPE_LIST_TRANSFORM_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename F, typename RESULT, typename ... Xs>
   struct transform_impl {
      using type = RESULT;
   };

   template<typename F, typename ... Ys, typename X, typename ... Xs>
   struct transform_impl<F, type_list<Ys...>, X, Xs...> {
      using type = typename transform_impl
         < F
         , type_list<Ys..., std::invoke_result_t<F, X>>
         , Xs...>::type;
   };
}

template<typename F, typename ... Ts>
using TL_transform_t = typename detail::transform_impl<std::decay_t<F>, type_list<>, Ts...>::type;

template<>
struct transform_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) {
      return TL_transform_t<F, Xs...>{};
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_TRANSFORM_H
