//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_GROUP_H
#define HOLO_GROUP_H

#include <holo/algo/apply_operator.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

struct group_t : apply_operator_1_t<group_algo> {};
constexpr group_t group{};

struct group_by_t : apply_operator_2_t<group_by_algo> {};
constexpr group_by_t group_by{};

HOLO_NS_END

#endif //HOLO_GROUP_H
