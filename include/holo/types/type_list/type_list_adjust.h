//
// Created by Darwin Yuan on 2020/9/9.
//

#ifndef HOLO_TYPE_LIST_ADJUST_H
#define HOLO_TYPE_LIST_ADJUST_H

#include <holo/types/type_list/type_list_t.h>

HOLO_NS_BEGIN

template<>
struct adjust_algo<type_list_tag> {
   template <typename X, typename F, typename ... Xs>
   constexpr static auto apply(type_c_t<X>, F, type_list<Xs...>) {
      using type = std::invoke_result_t<F, type_c_t<X>>;
      static_assert(Is_Type_C<type>);
      return make_type_list((type_c<X> == Xs{} ? type{} : Xs{})...);
   }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_ADJUST_H
