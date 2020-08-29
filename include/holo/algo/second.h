//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_SECOND_H
#define HOLO_SECOND_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct second_t : apply_operator_1_t<second_algo> {};
constexpr second_t second{};

HOLO_NS_END

#endif //HOLO_SECOND_H
