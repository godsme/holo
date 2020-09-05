//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TAKE_RIGHT_H
#define HOLO_TAKE_RIGHT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct take_right_t : apply_operator_2_t<take_right_algo> {};
constexpr take_right_t take_right{};

HOLO_NS_END

#endif //HOLO_TAKE_RIGHT_H
