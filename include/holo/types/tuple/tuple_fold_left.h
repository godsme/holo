//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_FOLD_LEFT_H
#define HOLO_TUPLE_FOLD_LEFT_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/algo/detail/pred.h>
#include <holo/types/detail/fold_helper.h>

HOLO_NS_BEGIN

template<> struct fold_left_algo<tuple_tag> {
   template<typename INIT, typename F, typename Xs, std::size_t ... Xn>
   constexpr static auto tuple_fold_left(INIT&& init, F&& f, Xs const& xs, std::index_sequence<Xn...>) {
      return (detail::fold_helper{init, f} << ... << get<Xn>(xs)).result_;
   }

   template<typename INIT, typename F, typename ... Xs>
   constexpr static auto apply(INIT&& init, F&& f, tuple<Xs...> const& xs) {
      return tuple_fold_left(std::forward<INIT>(init), std::forward<F>(f), xs, std::index_sequence_for<Xs...>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_FOLD_LEFT_H
