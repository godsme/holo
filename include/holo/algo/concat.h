//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONCAT_H
#define GRAPH_CONCAT_H

#include <holo/types/tuple.h>
#include <type_traits>
#include "partial_apply.h"

HOLO_NS_BEGIN

struct append_c {
private:
   template <typename T, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return tuple<Ts..., std::decay_t<T>>{};
   }

public:
   template <typename ... Ts, typename T>
   constexpr auto operator()(T&&, tuple<Ts...> stream) const {
      return invoke<T>(stream);
   }

   template <typename T>
   constexpr auto operator()(T&&) const {
      __return_invoke(T);
   }
};

constexpr append_c append{};

struct prepend_c {
private:
   template <typename T, typename ... Ts>
   constexpr static auto invoke(tuple<Ts...>) {
      return tuple<std::decay_t<T>, Ts...>{};
   }

public:
   template <typename T, typename ... Ts>
   constexpr auto operator()(T&&, tuple<Ts...> stream) const {
      return invoke<T>(stream);
   }

   template <typename T>
   constexpr auto operator()(T&&) const {
      __return_invoke(T);
   }
};

constexpr prepend_c prepend{};

template <typename ... Ts1, typename ...Ts2>
constexpr auto concat(tuple<Ts1...> const&, tuple<Ts2...> const&) {
   return tuple<Ts1..., Ts2...>{};
}

HOLO_NS_END

#endif //GRAPH_CONCAT_H
