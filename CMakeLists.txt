cmake_minimum_required(VERSION 3.16)
project(holo)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
)

add_executable(holo
        tests/test_holo.cpp
        tests/catch.cpp include/holo/algo/pipeline.h include/holo/holo.h include/holo/algo/partial_apply.h)