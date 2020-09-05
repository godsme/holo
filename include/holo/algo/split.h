//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_SPLIT_H
#define HOLO_SPLIT_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct split_t : apply_operator_2_t<split_algo> {};
constexpr split_t split{};

HOLO_NS_END

#endif //HOLO_SPLIT_H
