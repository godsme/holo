//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_ANY_OF_H
#define HOLO_ANY_OF_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct any_of_t : apply_operator_2_t<any_of_algo> {};
constexpr any_of_t any_of{};

HOLO_NS_END

#endif //HOLO_ANY_OF_H
