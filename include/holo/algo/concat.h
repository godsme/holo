//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONCAT_H
#define GRAPH_CONCAT_H

#include <holo/concept/append.h>
#include <holo/algo/detail/tag_of.h>
#include <utility>

HOLO_NS_BEGIN

struct concat_t {
private:
   template <typename Xs, typename Ys>
   constexpr static auto invoke(Xs&& xs, Ys&& ys) {
      return concat_impl<typename holo::tag_of<Xs>::type>::apply(xs, ys);
   }

public:
   template <typename Xs, typename Ys>
   constexpr auto operator()(Xs&& xs, Ys&& ys) const {
      return invoke(std::forward<Xs>(xs), std::forward<Ys>(ys));
   }

   template <typename Xs>
   constexpr auto operator()(Xs&& xs) const {
      return [=](auto stream) { return invoke(xs, stream); };
   }
};

constexpr concat_t concat{};

HOLO_NS_END

#endif //GRAPH_CONCAT_H
