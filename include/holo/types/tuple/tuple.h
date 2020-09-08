//
// Created by Darwin Yuan on 2020/8/28.
//

#ifndef __HOLO_TUPLE_H_
#define __HOLO_TUPLE_H_

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/tuple/tuple_head.h>
#include <holo/types/tuple/tuple_elem.h>
#include <holo/types/tuple/tuple_tail.h>
#include <holo/types/tuple/tuple_take.h>
#include <holo/types/tuple/tuple_drop.h>
#include <holo/types/tuple/tuple_contains.h>
#include <holo/types/tuple/tuple_concat.h>
#include <holo/types/tuple/tuple_prepend.h>
#include <holo/types/tuple/tuple_append.h>
#include <holo/types/tuple/tuple_filter.h>
#include <holo/types/tuple/tuple_remove_if.h>
#include <holo/types/tuple/tuple_transform.h>
#include <holo/types/tuple/tuple_find_if.h>
#include <holo/types/tuple/tuple_flatten.h>
#include <holo/types/tuple/tuple_fold_left.h>
#include <holo/types/tuple/tuple_partition.h>
#include <holo/types/tuple/tuple_reverse.h>
#include <holo/types/tuple/tuple_unique.h>
#include <holo/types/tuple/tuple_product.h>
#include <holo/types/tuple/tuple_sort.h>
#include <holo/types/tuple/tuple_length.h>
#include <holo/types/tuple/tuple_zip.h>

HOLO_NS_BEGIN
template<typename ... Ts, typename F, typename = std::enable_if_t<std::is_invocable_v<F, tuple<Ts...>>>>
constexpr auto operator | (tuple<Ts...> stream, F&& f) {
   return f(stream);
}
HOLO_NS_END

#endif

