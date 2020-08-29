//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REMOVE_IF_H
#define GRAPH_REMOVE_IF_H

#include <holo/concept/algo.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct remove_if_t {
private:
   template <typename F, typename Xs>
   constexpr static auto apply(F&& f, Xs&& xs) {
      return remove_if_algo<typename holo::tag_of<Xs>::type>::apply(f, xs);
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

constexpr remove_if_t remove_if{};

HOLO_NS_END

#endif //GRAPH_REMOVE_IF_H
