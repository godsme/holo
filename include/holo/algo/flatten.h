//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_FLATTEN_H
#define GRAPH_FLATTEN_H

#include <holo/types/tuple.h>

HOLO_NS_BEGIN

namespace {
   template <typename T>
   struct flatten_helper {
      constexpr flatten_helper(T value) : value_(value) {}
      using type = T;
      T value_;
   };

   template<typename ... Ts1, typename ... Ts2>
   constexpr auto operator+(flatten_helper<tuple<Ts1...>> acc, tuple<Ts2...> elem) {
      return flatten_helper{tuple<Ts1..., Ts2...>{}};
   }

   template<typename T>
   struct flatten_trait {
      using type = tuple<T>;
   };

   template<typename ... Ts>
   struct flatten_impl {
      using type = typename decltype((flatten_helper<tuple<>>{tuple<>{}} + ... + typename flatten_trait<Ts>::type{}))::type;
   };

   template<typename ... Ts>
   struct flatten_trait<tuple<Ts...>> {
      using type = typename flatten_impl<Ts...>::type;
   };
}

template<typename ... Ts>
using flatten_t = typename flatten_impl<Ts...>::type;

struct flatten_c {
   template<typename ... Ts>
   constexpr auto operator()(tuple<Ts...>) const {
      return flatten_t<Ts...>{};
   }

   constexpr auto operator()() const {
      return [this](auto stream) {
         return operator()(stream);
      };
   }
};

constexpr flatten_c flatten{};

HOLO_NS_END

#endif //GRAPH_FLATTEN_H
