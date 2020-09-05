//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_TAKE_H
#define HOLO_TYPE_LIST_TAKE_H

#include <holo/types/type_list/type_list_t.h>

HOLO_NS_BEGIN

namespace detail {
   template<std::size_t N, typename R, typename ... Xs>
   struct take_impl;

   template<std::size_t N, typename ... Rs, typename H, typename ... Xs>
   struct take_impl<N, type_list<Rs...>, H, Xs...> {
      using type = typename take_impl<N-1, type_list<Rs..., H>, Xs...>::type;
   };

   template<typename R, typename ... Xs>
   struct take_impl<0, R, Xs...> {
      using type = R;
   };
}

template<std::size_t N, typename ... Xs>
using TL_take_t = typename detail::take_impl<N, type_list<>, Xs...>::type;

template<>
struct take_algo<type_list_tag> {
   template<std::size_t N, typename ... Xs>
   constexpr static auto apply(size_c_t<N>, type_list<Xs...>) -> TL_take_t<N, Xs...> {
      static_assert(N <= sizeof...(Xs));
      return {};
   }
};


namespace detail {
   template<typename F, typename R, typename ... Xs>
   struct take_while_impl {
      using type = R;
   };

   template<typename F, typename ... Rs, typename H, typename ... Xs>
   struct take_while_impl<F, type_list<Rs...>, H, Xs...> {
      using type = std::conditional_t
         < detail::Is_Pred_Satisfied<F, H>
         , typename take_while_impl<F, type_list<Rs..., H>, Xs...>::type
         , type_list<Rs...>>;
   };
}

template<typename F, typename ... Xs>
using TL_take_while_t = typename detail::take_while_impl<F, type_list<>, Xs...>::type;

template<>
struct take_while_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) -> TL_take_while_t<F, Xs...> { return {}; }
};


HOLO_NS_END

#endif //HOLO_TYPE_LIST_TAKE_H
