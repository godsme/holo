//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_HEAD_H
#define GRAPH_HEAD_H

#include <holo/holo_ns.h>
#include <holo/types/type_list.h>
#include <holo/types/size_c.h>
#include <holo/types/integral_c.h>
#include <holo/algo/partial_apply.h>

HOLO_NS_BEGIN

template <typename TUPLE>
constexpr auto empty(const TUPLE& tuple) {
   return bool_c<std::tuple_size_v<TUPLE> == 0>;
}

template <typename ... Ts>
constexpr auto size(type_list<Ts...>) {
   return holo::size_c<sizeof...(Ts)>;
}

//////////////////////////////////////////////////////////////////////////
struct head_c {
private:
   template <typename ... Ts>
   constexpr static auto invoke(type_list<Ts...>) {
      return typename type_list<Ts...>::head{};
   }

public:
   template <typename ... Ts>
   constexpr auto operator()(type_list<Ts...> stream) const {
      return invoke(stream);
   }

   constexpr auto operator()() const {
      __return_invoke_0();
   }
};

constexpr head_c head{};

//////////////////////////////////////////////////////////////////////////
struct tail_c {
private:
   template <typename ... Ts>
   constexpr static auto invoke(type_list<Ts...>) {
      return typename type_list<Ts...>::tail{};
   }

public:
   template <typename ... Ts>
   constexpr auto operator()(type_list<Ts...> stream) const {
      return invoke(stream);
   }

   constexpr auto operator()() const {
      __return_invoke_0();
   }
};

constexpr tail_c tail{};

HOLO_NS_END

#endif //GRAPH_HEAD_H
