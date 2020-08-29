//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef HOLO_PRED_H
#define HOLO_PRED_H

#include <holo/types/type_c.h>
#include <type_traits>
#include <holo/types/integral_c.h>
#include <holo/algo/contains.h>

HOLO_NS_BEGIN

namespace detail {
   template<typename PRED, typename T>
   constexpr bool Is_Pred_Satisfied = std::is_same_v<std::invoke_result_t<std::decay_t<PRED>, T>, bool_c_t<true>>;

   template<typename H, typename RESULT>
   constexpr bool Contains = std::is_same_v<bool_c_t<true>, decltype(contains(std::declval<H>(), RESULT{}))>;
}

HOLO_NS_END

#endif //HOLO_PRED_H
