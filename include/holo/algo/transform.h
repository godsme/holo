//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_TRANSFORM_H
#define GRAPH_TRANSFORM_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct transform_t : apply_operator_2_t<transform_algo> {};
constexpr transform_t transform{};

HOLO_NS_END

#endif //GRAPH_TRANSFORM_H
