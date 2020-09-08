//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_ALGO_DEFS_H
#define HOLO_ALGO_DEFS_H

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

template<typename Tag>
struct flatten_algo;

template<typename Tag>
struct fold_left_algo;

template<typename Tag>
struct fold_left_1_algo;

template<typename Tag>
struct head_algo;

template<typename Tag>
struct tail_algo;

template<typename Tag>
struct take_algo;

template<typename Tag>
struct drop_algo;

template<typename Tag>
struct partition_algo;

template<typename Tag>
struct reverse_algo;

template<typename Tag>
struct unique_algo;

template<typename Tag>
struct elem_algo;

template<typename Tag>
struct product_algo;

template<typename Tag>
struct sort_algo;

template<typename Tag>
struct first_algo;

template<typename Tag>
struct second_algo;

template<typename Tag>
struct length_algo;

template<typename Tag>
struct zip_algo;

template<typename Tag>
struct zip_shortest_algo;

template<typename Tag>
struct zip3_algo;

template<typename Tag>
struct zip_with_algo;

template<typename Tag>
struct zip_shortest_with_algo;

template<typename Tag>
struct zip3_with_algo;

template<typename Tag>
struct empty_algo;

template<typename Tag>
struct group_algo;

template<typename Tag>
struct group_by_algo;

template<typename Tag>
struct any_of_algo;

template<typename Tag>
struct all_of_algo;

template<typename Tag>
struct none_of_algo;

template<typename Tag>
struct take_right_algo;

template<typename Tag>
struct drop_right_algo;

template<typename Tag>
struct last_algo;

template<typename Tag>
struct take_while_algo;

template<typename Tag>
struct drop_while_algo;

template<typename Tag>
struct split_algo;

template<typename Tag>
struct unpack_algo;

HOLO_NS_END

#endif //HOLO_ALGO_DEFS_H
