//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_HOLO_H
#define HOLO_HOLO_H

#include <holo/types/char_c.h>
#include <holo/types/tuple_trait.h>
#include <holo/types/pair.h>
#include <holo/algo/tail.h>
#include <holo/algo/fold_left.h>
#include <holo/algo/take.h>
#include <holo/algo/drop.h>
#include <holo/algo/append.h>
#include <holo/algo/prepend.h>
#include <holo/algo/find_if.h>
#include <holo/algo/transform.h>
#include <holo/algo/filter.h>
#include <holo/algo/contains.h>
#include <holo/algo/concat.h>
#include <holo/algo/remove_if.h>
#include <holo/algo/reverse.h>
#include <holo/algo/head.h>
#include <holo/algo/partition.h>
#include <holo/algo/sort.h>
#include <holo/types/sizeof_c.h>
#include <holo/algo/unique.h>
#include <holo/algo/flatten.h>
#include <holo/algo/product.h>
#include <holo/algo/first.h>
#include <holo/algo/second.h>
#include <holo/algo/length.h>
#include <holo/algo/zip.h>
#include <holo/algo/empty.h>

#define __HOLO_USE_TYPE_LIST 1

#if __HOLO_USE_TYPE_LIST
#include <holo/types/type_list/type_list.h>
#define __HOLO_make_tuple holo::make_type_list
#define __HOLO_make_pair  holo::make_type_pair
#define __HOLO_tuple_t    holo::type_list_t
#define __HOLO_tuple      holo::type_list
#define __HOLO_pair       holo::type_pair
#else
#include <holo/types/tuple/tuple.h>
#define __HOLO_make_tuple holo::make_tuple
#define __HOLO_make_pair  holo::make_pair
#define __HOLO_tuple_t    holo::tuple_t
#define __HOLO_tuple      holo::tuple
#define __HOLO_pair       holo::pair
#endif

#endif //HOLO_HOLO_H
