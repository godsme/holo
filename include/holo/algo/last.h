//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_LAST_H
#define HOLO_LAST_H

#include <holo/algo/apply_operator.h>
#include <holo/types/size_c.h>

HOLO_NS_BEGIN

struct last_t : apply_operator_1_t<last_algo> {};
constexpr last_t last{};

HOLO_NS_END

#endif //HOLO_LAST_H
