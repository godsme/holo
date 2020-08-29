//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef GRAPH_FILTER_H
#define GRAPH_FILTER_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct filter_t : apply_operator_2_t<filter_algo> {};

constexpr filter_t filter{};

HOLO_NS_END

#endif //GRAPH_FILTER_H
