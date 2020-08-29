//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_PARTITION_H
#define GRAPH_PARTITION_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct partition_t : apply_operator_2_t<partition_algo> {};
constexpr partition_t partition{};

HOLO_NS_END

#endif //GRAPH_PARTITION_H
