//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_NONE_OF_H
#define HOLO_NONE_OF_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct none_of_t : apply_operator_2_t<none_of_algo> {};
constexpr none_of_t none_of{};

HOLO_NS_END

#endif //HOLO_NONE_OF_H
