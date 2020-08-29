//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TAIL_H
#define HOLO_TAIL_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct tail_t : apply_operator_1_t<tail_algo> {};
constexpr tail_t tail{};

HOLO_NS_END

#endif //HOLO_TAIL_H
