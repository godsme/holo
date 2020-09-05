//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_DROP_WHILE_H
#define HOLO_TYPE_LIST_DROP_WHILE_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename F, typename ... Xs>
   struct drop_while_impl {
      using type = type_list<Xs...>;
   };

   template<typename F, typename H, typename ... Xs>
   struct drop_while_impl<F, H, Xs...> {
      using type = std::conditional_t
         < detail::Is_Pred_Satisfied<F, H>
            , typename drop_while_impl<F, Xs...>::type
            , type_list<H, Xs...>>;
   };
}

template<typename F, typename ... Xs>
using TL_drop_while_t = typename detail::drop_while_impl<F, Xs...>::type;

template<>
struct drop_while_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) -> TL_drop_while_t<F, Xs...> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_DROP_WHILE_H
