//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_H
#define HOLO_ALGO_H

#include <holo/holo_ns.h>

HOLO_NS_BEGIN

template<typename Tag>
struct append_algo;

template<typename Tag>
struct prepend_algo;

template<typename Tag>
struct concat_algo;

template<typename Tag>
struct contains_algo;

template<typename Tag>
struct filter_algo;

template<typename Tag>
struct remove_if_algo;

template<typename Tag>
struct transform_algo;

template<typename Tag>
struct find_if_algo;

HOLO_NS_END

#endif //HOLO_ALGO_H
