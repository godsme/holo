//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONTAINS_H
#define GRAPH_CONTAINS_H

#include <holo/holo_ns.h>
#include <type_traits>
#include <holo/types/integral_c.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

struct contains_c {
private:
   template <typename T, typename ... Ts>
   constexpr static auto invoke(type_list<Ts...>) {
      return bool_c<(std::is_same_v<Ts, std::decay_t<T>> || ...)>;
   }

public:
   template <typename T, typename ... Ts>
   constexpr auto operator()(T&& value, type_list<Ts...> stream) const {
      return invoke<T>(stream);
   }

   template <typename T>
   constexpr auto operator()(T&&) const {
      __return_invoke(T);
   }
};

constexpr contains_c contains{};

HOLO_NS_END

#endif //GRAPH_CONTAINS_H
