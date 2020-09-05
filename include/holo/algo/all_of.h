//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_ALL_OF_H
#define HOLO_ALL_OF_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct all_of_t : apply_operator_2_t<all_of_algo> {};
constexpr all_of_t all_of{};

HOLO_NS_END

#endif //HOLO_ALL_OF_H
