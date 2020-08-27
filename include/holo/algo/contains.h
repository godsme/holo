//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONTAINS_H
#define GRAPH_CONTAINS_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

struct contains_c {
   template <typename ... Ts, typename T>
   constexpr auto operator()(T&& value, tuple<Ts...>) const {
      return bool_c<(std::is_same_v<Ts, std::decay_t<T>> || ...)>;
   }

   template <typename T>
   constexpr auto operator()(T&& v) const {
      return [value = std::move(v), this]( auto stream ) {
         return (*this)(value, stream);
      };
   }
};

constexpr contains_c contains{};

HOLO_NS_END

#endif //GRAPH_CONTAINS_H
