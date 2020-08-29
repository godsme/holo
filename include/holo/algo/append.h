//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_APPEND_H
#define HOLO_ALGO_APPEND_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct append_t : apply_operator_2_t<append_algo> {};
constexpr append_t append{};

HOLO_NS_END

#endif //HOLO_ALGO_H
