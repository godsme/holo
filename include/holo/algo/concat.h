//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONCAT_H
#define GRAPH_CONCAT_H

#include <holo/types/type_list.h>
#include <type_traits>
#include "partial_apply.h"

HOLO_NS_BEGIN

struct append_c {
private:
   template <typename T, typename ... Ts>
   constexpr static auto invoke(type_list<Ts...>) {
      return type_list<Ts..., std::decay_t<T>>{};
   }

public:
   template <typename ... Ts, typename T>
   constexpr auto operator()(T&&, type_list<Ts...> stream) const {
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
   constexpr static auto invoke(type_list<Ts...>) {
      return type_list<std::decay_t<T>, Ts...>{};
   }

public:
   template <typename T, typename ... Ts>
   constexpr auto operator()(T&&, type_list<Ts...> stream) const {
      return invoke<T>(stream);
   }

   template <typename T>
   constexpr auto operator()(T&&) const {
      __return_invoke(T);
   }
};

constexpr prepend_c prepend{};

template <typename ... Ts1, typename ...Ts2>
constexpr auto concat(type_list<Ts1...> const&, type_list<Ts2...> const&) {
   return type_list<Ts1..., Ts2...>{};
}

HOLO_NS_END

#endif //GRAPH_CONCAT_H
