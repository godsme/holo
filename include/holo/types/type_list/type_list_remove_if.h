//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_REMOVE_IF_H
#define HOLO_TYPE_LIST_REMOVE_IF_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename RESULT, typename ... Ts>
   struct remove_if_impl {
      using type = RESULT;
   };

   template<typename PRED, typename ... Xs, typename H, typename ... Ts>
   struct remove_if_impl<PRED, type_list<Xs...>, H, Ts...> {
      using result = std::conditional_t<Is_Pred_Satisfied<PRED, H>,
            type_list<Xs...>,
            type_list<Xs..., H>>;
      using type = typename remove_if_impl<PRED, result, Ts...>::type;
   };
}

template<typename F, typename ... Ts>
using TL_remove_if_t = typename detail::remove_if_impl<F, type_list<>, Ts...>::type;

template<>
struct remove_if_algo<type_list_tag> {
   template <typename Pred, typename ... Xs>
   constexpr static auto apply(Pred, type_list<Xs...>) -> TL_remove_if_t<Pred, Xs...> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_REMOVE_IF_H
