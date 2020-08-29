//
// Created by godsme on 8/27/20.
//

#ifndef HOLO_APPLY_OPERATOR_H
#define HOLO_APPLY_OPERATOR_H

#include <holo/holo_ns.h>
#include <holo/algo/detail/tag_of.h>
#include <holo/concept/algo.h>
#include <utility>

HOLO_NS_BEGIN

template<template<typename> typename ALGO>
struct apply_operator_1_t {
private:
   template <typename Xs>
   constexpr static auto apply(Xs&& xs) {
      return ALGO<typename holo::tag_of<Xs>::type>::template apply(xs);
   }

public:
   template <typename Xs>
   constexpr auto operator()(Xs&& xs) const {
      return apply(std::forward<Xs>(xs));
   }

   constexpr auto operator()() const {
      return [=](auto xs) { return apply(xs); };
   }
};

template<template<typename> typename ALGO>
struct apply_operator_2_t {
private:
   template <typename F, typename Xs>
   constexpr static auto apply(F&& f, Xs&& xs) {
      return ALGO<typename holo::tag_of<Xs>::type>::template apply(f, xs);
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

HOLO_NS_END

#endif //HOLO_APPLY_OPERATOR_H
