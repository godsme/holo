//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_PIPELINE_H
#define HOLO_PIPELINE_H

#include <holo/types/type_list/type_list.h>
#include <holo/types/tuple/tuple.h>

HOLO_NS_BEGIN

template<typename ... Ts, typename F, typename = std::enable_if_t<std::is_invocable_v<F, type_list<Ts...>>>>
constexpr auto operator | (type_list<Ts...> stream, F&& f) {
   return f(stream);
}

template<typename ... Ts, typename F, typename = std::enable_if_t<std::is_invocable_v<F, tuple<Ts...>>>>
constexpr auto operator | (tuple<Ts...> stream, F&& f) {
   return f(stream);
}

HOLO_NS_END

#endif //HOLO_PIPELINE_H
