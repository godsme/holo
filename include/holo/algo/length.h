//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_LENGTH_H
#define HOLO_LENGTH_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct length_t : apply_operator_1_t<length_algo> {};
constexpr length_t length{};

HOLO_NS_END

#endif //HOLO_LENGTH_H
