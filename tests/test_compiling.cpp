//
// Created by godsme on 8/29/20.
//


#include <holo/types/tuple/tuple_partition.h>
#include <iostream>

void f() {
    holo::pair pair1{1, 2};
    holo::pair pair2{3, 4};

    if(pair1 == pair2) {
        std::cout << "eq" << std::endl;
    }

    holo::partition_algo<holo::tuple_tag>::apply([](auto){return holo::true_c;}
    , holo::tuple_t<int, double>);
}