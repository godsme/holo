//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_EMPTY_H
#define HOLO_EMPTY_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct empty_t : apply_operator_2_t<empty_algo> {};
constexpr empty_t empty{};

HOLO_NS_END

#endif //HOLO_EMPTY_H
