//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef HOLO_FOLD_LEFT_H
#define HOLO_FOLD_LEFT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct fold_left_t : apply_operator_3_t<fold_left_algo> {};
constexpr fold_left_t fold_left{};

struct fold_left_1_t : apply_operator_2_t<fold_left_1_algo> {};
constexpr fold_left_1_t fold_left_1{};

HOLO_NS_END

#endif //HOLO_FOLD_LEFT_H
