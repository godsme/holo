cmake_minimum_required(VERSION 3.16)
project(holo)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
)

add_executable(holo
        tests/test_holo.cpp
        tests/catch.cpp include/holo/algo/pipeline.h include/holo/holo.h include/holo/algo/partial_apply.h include/holo/types/detail/ebo.h include/holo/types/tuple/tuple.h tests/test_tuple.cpp include/holo/concept/algo.h include/holo/algo/detail/tag_of.h include/holo/algo/append.h include/holo/algo/prepend.h include/holo/types/non_comparable.h include/holo/types/tuple/tuple_contains.h include/holo/types/tuple/tuple_t.h include/holo/types/tuple/tuple_concat.h include/holo/types/tuple/tuple_append.h include/holo/types/tuple/tuple_prepend.h include/holo/types/tuple/tuple_filter.h)