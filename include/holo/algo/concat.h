//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONCAT_H
#define GRAPH_CONCAT_H

#include <holo/types/tuple.h>
#include <type_traits>

HOLO_NS_BEGIN

struct append_c {
   template <typename ... Ts, typename T>
   constexpr auto operator()(T&&, tuple<Ts...>) const {
      return tuple<Ts..., std::decay_t<T>>{};
   }

   template <typename T>
   constexpr auto operator()(T&& v) const {
      return [value = std::move(v), this](auto stream) {
         return operator()(value, stream);
      };
   }
};

constexpr append_c append{};

struct prepend_c {
   template <typename ... Ts, typename T>
   constexpr auto operator()(T&&, tuple<Ts...>) const {
      return tuple<std::decay_t<T>, Ts...>{};
   }

   template <typename T>
   constexpr auto operator()(T&& v) const {
      return [value = std::move(v), this](auto stream) {
         return operator()(value, stream);
      };
   }
};

constexpr prepend_c prepend{};

template <typename ... Ts1, typename ...Ts2>
constexpr auto concat(tuple<Ts1...> const&, tuple<Ts2...> const&) {
   return tuple<Ts1..., Ts2...>{};
}

HOLO_NS_END

#endif //GRAPH_CONCAT_H
