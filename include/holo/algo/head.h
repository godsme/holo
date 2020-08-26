//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_HEAD_H
#define GRAPH_HEAD_H

#include <holo/holo_ns.h>
#include <holo/types/tuple.h>
#include <holo/types/size_c.h>
#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

template <typename TUPLE>
constexpr auto empty(const TUPLE& tuple) {
   return bool_c<std::tuple_size_v<TUPLE> == 0>;
}

template <typename ... Ts>
constexpr auto size(tuple<Ts...>) {
   return holo::size_c<sizeof...(Ts)>;
}

struct head_c {
   template <typename ... Ts>
   constexpr auto operator()(tuple<Ts...>) const {
      return typename tuple<Ts...>::head{};
   }

   constexpr auto operator()() const {
      return [this](auto stream) {
         return operator()(stream);
      };
   }
};

constexpr head_c head{};

struct tail_c {
   template <typename ... Ts>
   constexpr auto operator()(tuple<Ts...>) const {
      return typename tuple<Ts...>::tail{};
   }

   constexpr auto operator()() const {
      return [this](auto stream) {
         return operator()(stream);
      };
   }
};

constexpr tail_c tail{};

HOLO_NS_END

#endif //GRAPH_HEAD_H
