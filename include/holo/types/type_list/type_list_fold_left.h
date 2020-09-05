//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FOLD_LEFT_H
#define HOLO_TYPE_LIST_FOLD_LEFT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/detail/fold_helper.h>

HOLO_NS_BEGIN

template<>
struct fold_left_algo<type_list_tag> {
   template <typename INIT, typename F, typename ... Xs>
   constexpr static auto apply(INIT const& init, F const& f, type_list<Xs...>) {
      return (detail::fold_helper{init, f} <<  ... << Xs{})();
   }
};

template<>
struct fold_left_1_algo<type_list_tag> {
   template <typename F, typename X1, typename X2, typename ... Xs>
   constexpr static auto apply(F&& f, type_list<X1, X2, Xs...>) {
      return (detail::fold_helper{f(X1{}, X2{}), std::forward<F>(f)} <<  ... << Xs{})();
   }

   template <typename F, typename X>
   constexpr static auto apply(F&&, type_list<X>) -> type_list<X> { return {}; }

   template <typename F>
   constexpr static auto apply(F&&, type_list<>) -> type_list<> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FOLD_LEFT_H
