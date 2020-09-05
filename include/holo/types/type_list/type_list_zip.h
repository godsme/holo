//
// Created by Darwin Yuan on 2020/9/5.
//

#ifndef HOLO_TYPE_LIST_ZIP_H
#define HOLO_TYPE_LIST_ZIP_H

#include <holo/types/type_list/type_list_t.h>
#include <holo/types/type_pair.h>

HOLO_NS_BEGIN

template<> struct zip_algo<type_list_tag> {
   template<typename ... Xs, typename ... Ys>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>)
      -> type_list<type_pair<Xs, Ys>...> { return {}; }
};

template<> struct zip3_algo<type_list_tag> {
   template<typename ... Xs, typename ... Ys, typename ... Zs>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>, type_list<Zs...>)
   -> type_list<type_list<Xs, Ys, Zs>...> { return {}; }
};


template<> struct zip_with_algo<type_list_tag> {
   template<typename F, typename ... Xs, typename ... Ys>
   constexpr static auto apply(F, type_list<Xs...>, type_list<Ys...>)
   -> type_list<std::invoke_result_t<F, Xs, Ys>...> { return {}; }
};

template<> struct zip3_with_algo<type_list_tag> {
   template<typename F, typename ... Xs, typename ... Ys, typename ... Zs>
   constexpr static auto apply(type_list<Xs...>, type_list<Ys...>, type_list<Zs...>)
   -> type_list<std::invoke_result_t<Xs, Ys, Zs>...> { return {}; }
};

HOLO_NS_END

#endif //HOLO_TYPE_LIST_ZIP_H
