//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_FOLD_LEFT_H
#define HOLO_TYPE_LIST_FOLD_LEFT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/concept/algo.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

namespace detail {
   template <typename T, typename F>
   struct fold_helper {
      constexpr fold_helper(T value, F f) : value_(value), f_(f) {}
      T value_;
      F f_;
   };

   template<typename T, typename F, typename ELEM>
   constexpr auto operator<<(fold_helper<T, F> acc, ELEM elem) {
      return fold_helper{acc.f_(acc.value_, elem), acc.f_};
   }
}

template<>
struct fold_left_algo<type_list_tag> {
   template <typename INIT, typename F, typename ... Xs>
   constexpr static auto apply(INIT&& init, F&& f,  type_list<Xs...>) {
      auto result = (detail::fold_helper{init, f} <<  ... << Xs{});
      return result.value_;
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_FOLD_LEFT_H
