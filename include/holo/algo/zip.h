//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_ZIP_H
#define HOLO_ZIP_H

#include <holo/algo/apply_operator.h>

HOLO_NS_BEGIN

struct zip_t : apply_operator_2_t<zip_algo> {};
constexpr zip_t zip{};

struct zip_shortest_t : apply_operator_2_t<zip_shortest_algo> {};
constexpr zip_shortest_t zip_shortest{};

struct zip3_t : apply_operator_3_t<zip3_algo> {};
constexpr zip3_t zip3{};

struct zip_with_t : apply_operator_3_t<zip_with_algo> {};
constexpr zip_with_t zip_with{};

struct zip_shortest_with_t : apply_operator_3_t<zip_shortest_with_algo> {};
constexpr zip_shortest_with_t zip_shortest_with{};

struct zip3_with_t : apply_operator_4_t<zip3_with_algo> {};
constexpr zip3_with_t zip3_with{};

HOLO_NS_END

#endif //HOLO_ZIP_H
