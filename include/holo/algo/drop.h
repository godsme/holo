//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_DROP_H
#define HOLO_DROP_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct drop_t : apply_operator_2_t<drop_algo> {};
constexpr drop_t drop{};

struct drop_while_t : apply_operator_2_t<drop_while_algo> {};
constexpr drop_while_t drop_while{};

HOLO_NS_END

#endif //HOLO_DROP_H
