//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_TYPE_LIST_H
#define HOLO_TYPE_LIST_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_list/type_list_elem.h>
#include <holo/types/type_list/type_list_head.h>
#include <holo/types/type_list/type_list_tail.h>
#include <holo/types/type_list/type_list_length.h>
#include <holo/types/type_list/type_list_filter.h>
#include <holo/types/type_list/type_list_remove_if.h>
#include <holo/types/type_list/type_list_find_if.h>
#include <holo/types/type_list/type_list_concat.h>
#include <holo/types/type_list/type_list_append.h>
#include <holo/types/type_list/type_list_prepend.h>
#include <holo/types/type_list/type_list_contains.h>
#include <holo/types/type_list/type_list_transform.h>
#include <holo/types/type_list/type_list_flatten.h>
#include <holo/types/type_list/type_list_fold_left.h>
#include <holo/types/type_list/type_list_partition.h>
#include <holo/types/type_list/type_list_reverse.h>
#include <holo/types/type_list/type_list_unique.h>
#include <holo/types/type_list/type_list_product.h>
#include <holo/types/type_list/type_list_sort.h>
#include <holo/types/type_list/type_list_zip.h>
#include <holo/types/type_list/type_list_take.h>
#include <holo/types/type_list/type_list_drop.h>
#include <holo/types/type_list/type_list_empty.h>
#include <holo/types/type_list/type_list_group.h>
#include <holo/types/type_list/type_list_any_of.h>
#include <holo/types/type_list/type_list_all_of.h>
#include <holo/types/type_list/type_list_none_of.h>
#include <holo/types/type_list/type_list_take_right.h>
#include <holo/types/type_list/type_list_drop_while.h>

HOLO_NS_BEGIN

template<typename ... Ts, typename F, typename = std::enable_if_t<std::is_invocable_v<F, type_list<Ts...>>>>
constexpr auto operator | (type_list<Ts...> stream, F&& f) {
   return f(stream);
}

HOLO_NS_END

#endif
