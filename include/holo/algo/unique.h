//
// Created by Darwin Yuan on 2020/8/14.
//

#ifndef HOLO_UNIQUE_H
#define HOLO_UNIQUE_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct unique_t : apply_operator_1_t<unique_algo> {};
constexpr unique_t unique{};

HOLO_NS_END

#endif //HOLO_UNIQUE_H
