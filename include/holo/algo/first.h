//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef HOLO_FIRST_H
#define HOLO_FIRST_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct first_t : apply_operator_1_t<first_algo> {};
constexpr first_t first{};

HOLO_NS_END

#endif //HOLO_FIRST_H
