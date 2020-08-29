//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_REMOVE_IF_H
#define GRAPH_REMOVE_IF_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct remove_if_t : apply_operator_2_t<remove_if_algo> {};
constexpr remove_if_t remove_if{};

HOLO_NS_END

#endif //GRAPH_REMOVE_IF_H
