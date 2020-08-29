//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ELEM_H
#define HOLO_ELEM_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct elem_t : apply_operator_2_t<elem_algo> {};
constexpr elem_t elem{};

HOLO_NS_END

#endif //HOLO_ELEM_H
