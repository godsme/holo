//
// Created by godsme on 8/27/20.
//

#ifndef HOLO_APPLY_OPERATOR_H
#define HOLO_APPLY_OPERATOR_H

#include <holo/algo/detail/tag_of.h>
#include <holo/concept/algo.h>
#include <utility>

HOLO_NS_BEGIN

template<template<typename> typename ALGO>
struct apply_operator_1_t {
private:
   template <typename Xs>
   constexpr static auto apply(Xs&& xs) {
      return ALGO<typename holo::tag_of<Xs>::type>::template apply(std::forward<Xs>(xs));
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
      return ALGO<typename holo::tag_of<Xs>::type>::template apply
            ( std::forward<F>(f)
            , std::forward<Xs>(xs));
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

template<template<typename> typename ALGO>
struct apply_operator_3_t {
private:
   template <typename ARG1, typename ARG2, typename Xs>
   constexpr static auto apply(ARG1&& arg1, ARG2&& arg2, Xs&& xs) {
      return ALGO<typename holo::tag_of<Xs>::type>::template apply
         ( std::forward<ARG1>(arg1)
         , std::forward<ARG2>(arg2)
         , std::forward<Xs>(xs));
   }

public:
   template <typename ARG1, typename ARG2, typename Xs>
   constexpr auto operator()(ARG1&& arg1, ARG2&& arg2, Xs&& xs) const {
      return apply(std::forward<ARG1>(arg1), std::forward<ARG2>(arg2), std::forward<Xs>(xs));
   }

   template <typename ARG1, typename ARG2>
   constexpr auto operator()(ARG1&& arg1, ARG2&& arg2) const {
      return [=](auto xs) { return apply(arg1, arg2, xs); };
   }
};

   template<template<typename> typename ALGO>
   struct apply_operator_4_t {
   private:
      template <typename ARG1, typename ARG2, typename ARG3, typename Xs>
      constexpr static auto apply(ARG1&& arg1, ARG2&& args2, ARG3&& args3, Xs&& xs) {
         return ALGO<typename holo::tag_of<Xs>::type>::template apply
            ( std::forward<ARG1>(arg1)
            , std::forward<ARG2>(args2)
            , std::forward<ARG3>(args3)
            , std::forward<Xs>(xs));
      }

   public:
      template <typename ARG1, typename ARG2, typename ARG3, typename Xs>
      constexpr auto operator()(ARG1&& arg1, ARG2&& arg2, ARG3&& arg3, Xs&& xs) const {
         return apply
            ( std::forward<ARG1>(arg1)
            , std::forward<ARG2>(arg2)
            , std::forward<ARG3>(arg3)
            , std::forward<Xs>(xs));
      }

      template <typename ARG1, typename ARG2>
      constexpr auto operator()(ARG1&& arg1, ARG2&& arg2) const {
         return [=](auto xs) { return apply(arg1, arg2, xs); };
      }
   };

HOLO_NS_END

#endif //HOLO_APPLY_OPERATOR_H
