//
// Created by Darwin Yuan on 2020/8/18.
//

#ifndef HOLO_FIND_IF_H
#define HOLO_FIND_IF_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct find_if_t : apply_operator_2_t<find_if_algo> {};
constexpr find_if_t find_if{};

HOLO_NS_END

#endif //HOLO_FIND_IF_H
