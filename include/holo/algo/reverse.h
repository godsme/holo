//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_REVERSE_H
#define HOLO_REVERSE_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct reverse_t : apply_operator_1_t<reverse_algo> {};
constexpr reverse_t reverse{};

HOLO_NS_END

#endif //HOLO_REVERSE_H
