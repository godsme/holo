//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_TYPE_PAIR_H
#define HOLO_TYPE_PAIR_H

#include <holo/types/type_list/type_list_t.h>
#include <type_traits>

HOLO_NS_BEGIN

struct type_pair_tag{};

template<typename T1, typename T2>
struct type_pair : type_list<T1, T2> {
   using tag_type = type_pair_tag;
   using first  = T1;
   using second = T2;
};

template<typename T1, typename T2>
constexpr type_pair<type_c_t< T1>, type_c_t<T2>> type_pair_t{};

template<typename T1, typename T2>
constexpr auto make_type_pair(T1 const&, T2 const&)
   -> type_pair<std::decay_t<T1>, std::decay_t<T2>> { return {}; }

template<> struct first_algo<type_pair_tag> {
   template<typename T1, typename T2>
   constexpr static auto apply(type_pair<T1, T2>) -> T1 { return {}; }
};

template<> struct second_algo<type_pair_tag> {
   template<typename T1, typename T2>
   constexpr static auto apply(type_pair<T1, T2>) -> T2 { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_PAIR_H
