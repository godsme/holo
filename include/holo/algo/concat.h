//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_CONCAT_H
#define GRAPH_CONCAT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct concat_t : apply_operator_2_t<concat_algo> {};
constexpr concat_t concat{};

HOLO_NS_END

#endif //GRAPH_CONCAT_H
