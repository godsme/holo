//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef GRAPH_FOLD_LEFT_H
#define GRAPH_FOLD_LEFT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct fold_left_t : apply_operator_3_t<fold_left_algo> {};
constexpr fold_left_t fold_left{};

HOLO_NS_END

#endif //GRAPH_FOLD_LEFT_H
