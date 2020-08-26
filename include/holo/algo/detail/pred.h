//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef GRAPH_PRED_H
#define GRAPH_PRED_H

#include <holo/types/type_c.h>
#include <type_traits>
#include <holo/types/integral_c.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename T>
   constexpr bool Is_Pred_Satisfied = std::is_same_v<std::invoke_result_t<std::decay_t<PRED>, T>, bool_c_t<true>>;
}

HOLO_NS_END

#endif //GRAPH_PRED_H