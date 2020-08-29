//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_AP_H
#define GRAPH_AP_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct product_t : apply_operator_2_t<product_algo> {};
constexpr product_t product{};

HOLO_NS_END

#endif //GRAPH_AP_H
