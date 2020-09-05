cmake_minimum_required(VERSION 3.16)
project(holo)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor \
      -Wcast-align -Wunused -Woverloaded-virtual -Wconversion \
      -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 \
      -Wno-invalid-offsetof  ")

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
)

add_executable(holo
        tests/test_holo.cpp
        tests/catch.cpp include/holo/holo.h include/holo/algo/apply_operator.h include/holo/types/detail/ebo.h include/holo/types/tuple/tuple.h tests/test_tuple.cpp include/holo/concept/algo.h include/holo/algo/detail/tag_of.h include/holo/algo/append.h include/holo/algo/prepend.h include/holo/types/non_comparable.h include/holo/types/tuple/tuple_contains.h include/holo/types/tuple/tuple_t.h include/holo/types/tuple/tuple_concat.h include/holo/types/tuple/tuple_append.h include/holo/types/tuple/tuple_prepend.h include/holo/types/tuple/tuple_filter.h include/holo/types/detail/filter_result.h include/holo/types/type_list/type_list_filter.h include/holo/types/type_list/type_list_t.h include/holo/types/type_list/type_list_concat.h include/holo/types/type_list/type_list_append.h include/holo/types/type_list/type_list_prepend.h include/holo/types/type_list/type_list_contains.h include/holo/types/type_list/type_list_remove_if.h include/holo/types/tuple/tuple_remove_if.h include/holo/types/type_list/type_list_transform.h include/holo/types/tuple/tuple_transform.h include/holo/types/type_list/type_list_find_if.h include/holo/types/tuple/tuple_find_if.h include/holo/types/type_list/type_list_flatten.h include/holo/types/tuple/tuple_flatten.h include/holo/types/type_list/type_list_fold_left.h include/holo/types/tuple/tuple_fold_left.h include/holo/types/detail/fold_helper.h include/holo/types/type_list/type_list_head.h include/holo/types/type_list/type_list_tail.h include/holo/algo/tail.h include/holo/types/tuple/tuple_head.h include/holo/types/tuple/tuple_tail.h include/holo/types/tuple/tuple_drop.h include/holo/algo/drop.h include/holo/types/tuple/tuple_take.h include/holo/algo/take.h include/holo/types/type_list/type_list_partition.h include/holo/types/tuple/tuple_partition.h include/holo/types/pair.h include/holo/types/type_list/type_list_reverse.h include/holo/types/tuple/tuple_reverse.h include/holo/types/type_list/type_list_unique.h include/holo/types/tuple/tuple_unique.h include/holo/types/type_list/type_list_elem.h include/holo/types/tuple/tuple_elem.h include/holo/algo/elem.h include/holo/types/type_list/type_list_product.h include/holo/types/tuple/tuple_product.h include/holo/types/type_list/type_list_sort.h include/holo/types/tuple/tuple_sort.h include/holo/algo/first.h include/holo/algo/second.h include/holo/algo/length.h include/holo/types/tuple/tuple_length.h tests/test_more.cpp include/holo/types/type_list/type_list_length.h include/holo/types/detail/foldl1.h include/holo/types/type_list/type_list_zip.h include/holo/algo/zip.h include/holo/types/type_list/type_list_take.h include/holo/types/type_list/type_list_drop.h include/holo/types/type_list/type_list_empty.h include/holo/algo/empty.h)