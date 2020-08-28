//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_PREPEND_H
#define HOLO_ALGO_PREPEND_H

#include <holo/concept/algo.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct prepend_t {
private:
   template <typename X, typename Xs>
   constexpr static auto apply(X&& x, Xs&& xs) {
      return prepend_algo<typename holo::tag_of<Xs>::type>::apply(x, xs);
   }

public:
   template <typename X, typename Xs>
   constexpr auto operator()(X&& x, Xs&& xs) const {
      return apply(std::forward<X>(x), std::forward<Xs>(xs));
   }

   template <typename X>
   constexpr auto operator()(X&& x) const {
      return [=](auto stream) { return apply(x, stream); };
   }
};

constexpr prepend_t prepend{};

HOLO_NS_END

#endif //HOLO_PREPEND_H
