//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_CONTAINS_H
#define HOLO_CONTAINS_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct contains_t : apply_operator_2_t<contains_algo> {};
constexpr contains_t contains{};

HOLO_NS_END

#endif //HOLO_CONTAINS_H
