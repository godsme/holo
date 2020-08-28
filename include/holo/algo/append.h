//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_APPEND_H
#define HOLO_ALGO_APPEND_H

#include <holo/concept/append.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct append_t {
private:
   template <typename X, typename Xs>
   constexpr static auto invoke(X&& x, Xs&& xs) {
      return append_impl<typename holo::tag_of<Xs>::type>::apply(x, xs);
   }

public:
   template <typename X, typename Xs>
   constexpr auto operator()(X&& x, Xs&& xs) const {
      return invoke(std::forward<X>(x), std::forward<Xs>(xs));
   }

   template <typename X>
   constexpr auto operator()(X&& x) const {
      return [=](auto stream) { return invoke(x, stream); };
   }
};

constexpr append_t append{};

HOLO_NS_END

#endif //HOLO_APPEND_H
