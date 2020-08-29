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
   constexpr static auto apply(INIT&& init, F&& f,  type_list<Xs...>) {
      return (detail::fold_helper{init, std::forward<F>(f)} <<  ... << Xs{}).result_;
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FOLD_LEFT_H
