//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_SORT_H
#define HOLO_SORT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct sort_t : apply_operator_2_t<sort_algo> {};
constexpr sort_t sort{};

HOLO_NS_END

#endif //HOLO_SORT_H
