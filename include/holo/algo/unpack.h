//
// Created by Darwin Yuan on 2020/9/8.
//

#ifndef HOLO_UNPACK_H
#define HOLO_UNPACK_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct unpack_t : apply_operator_2_t<unpack_algo> {};
constexpr unpack_t unpack{};

HOLO_NS_END

#endif //HOLO_UNPACK_H
