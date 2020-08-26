//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_AP_H
#define GRAPH_AP_H

#include <holo/types/tuple.h>
#include <holo/types/pair.h>
#include <holo/algo/flatten.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename T, typename ... Ts>
   struct ap_impl {
      using type = tuple<pair<T, Ts> ...>;
   };
}

template<typename ... Ts1, typename ... Ts2>
constexpr auto ap(tuple<Ts1...> const&, tuple<Ts2...> const&) {
   return flatten_t<typename detail::ap_impl<Ts1, Ts2...>::type ...>{};
}

HOLO_NS_END

#endif //GRAPH_AP_H
