//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_FLATTEN_H
#define GRAPH_FLATTEN_H

#include <holo/types/type_list.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

namespace {
   template <typename T>
   struct flatten_helper {
      constexpr flatten_helper(T value) : value_(value) {}
      using type = T;
      T value_;
   };

   template<typename ... Ts1, typename ... Ts2>
   constexpr auto operator+(flatten_helper<type_list<Ts1...>> acc, type_list<Ts2...> elem) {
      return flatten_helper{type_list<Ts1..., Ts2...>{}};
   }

   template<typename T>
   struct flatten_trait {
      using type = type_list<T>;
   };

   template<typename ... Ts>
   struct flatten_impl {
      using type = typename decltype((flatten_helper<type_list<>>{type_list<>{}} + ... + typename flatten_trait<Ts>::type{}))::type;
   };

   template<typename ... Ts>
   struct flatten_trait<type_list<Ts...>> {
      using type = typename flatten_impl<Ts...>::type;
   };
}

template<typename ... Ts>
using flatten_t = typename flatten_impl<Ts...>::type;

struct flatten_c {
private:
   template<typename ... Ts>
   constexpr static auto invoke(type_list<Ts...>) {
      return flatten_t<Ts...>{};
   }

public:
   template<typename ... Ts>
   constexpr auto operator()(type_list<Ts...> stream) const {
      return invoke(stream);
   }

   constexpr auto operator()() const {
      __return_invoke_0();
   }
};

constexpr flatten_c flatten{};

HOLO_NS_END

#endif //GRAPH_FLATTEN_H
