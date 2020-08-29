//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TAKE_H
#define HOLO_TAKE_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct take_t : apply_operator_2_t<take_algo> {};
constexpr take_t take{};

HOLO_NS_END

#endif //HOLO_TAKE_H
