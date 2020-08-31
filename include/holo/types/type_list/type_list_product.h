//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TYPE_LIST_PRODUCT_H
#define HOLO_TYPE_LIST_PRODUCT_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_pair.h>
#include <holo/types/type_list/type_list_flatten.h>

HOLO_NS_BEGIN

template<> struct product_algo<type_list_tag> {
private:
   template<typename X, typename ... Ys>
   using product = type_list<type_pair<X, Ys> ...>;

public:
   template <typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>) {
      return (product<Xs, Ys...>{} + ...);
   }

   template <typename ... Ys>
   constexpr static auto apply(type_list<>, type_list<Ys...>) -> type_list<> { return {}; }

   template <typename ... Xs>
   constexpr static auto apply(type_list<Xs...>, type_list<>) -> type_list<> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_PRODUCT_H
