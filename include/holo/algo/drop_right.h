//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_DROP_RIGHT_H
#define HOLO_DROP_RIGHT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct drop_right_t : apply_operator_2_t<drop_right_algo> {};
constexpr drop_right_t drop_right{};

HOLO_NS_END

#endif //HOLO_DROP_RIGHT_H
