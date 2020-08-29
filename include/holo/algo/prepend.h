//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_PREPEND_H
#define HOLO_ALGO_PREPEND_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct prepend_t : apply_operator_2_t<prepend_algo> {};
constexpr prepend_t prepend{};

HOLO_NS_END

#endif //HOLO_PREPEND_H
