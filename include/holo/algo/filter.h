//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <holo/concept/algo.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct filter_t {
private:
   template <typename F, typename Xs>
   constexpr static auto apply(F&& f, Xs&& xs) {
      return filter_algo<typename holo::tag_of<Xs>::type>::apply(f, xs);
   }

public:
   template <typename F, typename Xs>
   constexpr auto operator()(F&& f, Xs&& xs) const {
      return apply(std::forward<F>(f), std::forward<Xs>(xs));
   }

   template <typename F>
   constexpr auto operator()(F&& f) const {
      return [=](auto xs) { return apply(f, xs); };
   }
};

constexpr filter_t filter{};

HOLO_NS_END

#endif //GRAPH_FILTER_H
