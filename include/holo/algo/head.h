//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_HEAD_H
#define HOLO_HEAD_H

#include <holo/algo/apply_operator.h>
#include <holo/types/integral_constant/size_c.h>

HOLO_NS_BEGIN

struct head_t : apply_operator_1_t<head_algo> {};
constexpr head_t head{};

HOLO_NS_END

#endif //HOLO_HEAD_H
