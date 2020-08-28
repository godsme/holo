//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONTAINS_H
#define GRAPH_CONTAINS_H

#include <holo/concept/algo.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct contains_t {
private:
   template <typename X, typename Xs>
   constexpr static auto apply(X&& x, Xs&& xs) {
      return contains_algo<typename holo::tag_of<Xs>::type>::apply(x, xs);
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

constexpr contains_t contains{};

HOLO_NS_END

#endif //GRAPH_CONTAINS_H
