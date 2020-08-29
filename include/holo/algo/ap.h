//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_AP_H
#define GRAPH_AP_H

#include <holo/types/type_list/type_list.h>
#include <holo/types/pair.h>
#include <holo/algo/flatten.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename T, typename ... Ts>
   struct ap_impl {
      using type = type_list<pair<T, Ts> ...>;
   };
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto ap(type_list<Ts1...> const&, type_list<Ts2...> const&) {
   return TL_flatten_t<typename detail::ap_impl<Ts1, Ts2...>::type ...>{};
}

HOLO_NS_END

#endif //GRAPH_AP_H
