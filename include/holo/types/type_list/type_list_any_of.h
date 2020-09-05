//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_ANY_OF_H
#define HOLO_TYPE_LIST_ANY_OF_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/algo/detail/pred.h>

HOLO_NS_BEGIN

template<>
struct any_of_algo<type_list_tag> {
   template <typename F, typename ... Xs>
   constexpr static auto apply(F, type_list<Xs...>) {
      return bool_c<(detail::Is_Pred_Satisfied<F, Xs> || ...)>;
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_ANY_OF_H
