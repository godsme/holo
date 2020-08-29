//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_HEAD_H
#define GRAPH_HEAD_H

#include <holo/algo/apply_operator.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

template <typename T>
constexpr auto size(T const& container) {
   return size_c<T::size>;
}

struct head_t : apply_operator_1_t<head_algo> {};
constexpr head_t head{};

HOLO_NS_END

#endif //GRAPH_HEAD_H
