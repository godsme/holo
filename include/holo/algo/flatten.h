//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_FLATTEN_H
#define GRAPH_FLATTEN_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct flatten_t : apply_operator_1_t<flatten_algo> {};
constexpr flatten_t flatten{};

HOLO_NS_END

#endif //GRAPH_FLATTEN_H
