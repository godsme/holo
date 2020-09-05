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


namespace detail {
   template<typename F, typename Xs, typename Ys, typename ... Rs>
   struct zip_impl;

   template<typename F, typename X, typename ... Xs, typename Y, typename ... Ys, typename ... Rs>
   struct zip_impl<F, type_list<X, Xs...>, type_list<Y, Ys...>, Rs...> {
      using type = typename zip_impl<F, type_list<Xs...>, type_list<Ys...>, Rs..., std::invoke_result_t<F, X, Y>>::type;
   };

   template<typename F, typename Y, typename ... Ys, typename ... Rs>
   struct zip_impl<F, type_list<>, type_list<Y, Ys...>, Rs...> {
      using type = type_list<Rs...>;
   };

   template<typename F, typename X, typename ... Xs, typename ... Rs>
   struct zip_impl<F, type_list<X, Xs...>, type_list<>, Rs...> {
      using type = type_list<Rs...>;
   };

   template<typename F, typename ... Rs>
   struct zip_impl<F, type_list<>, type_list<>, Rs...> {
      using type = type_list<Rs...>;
   };
}

template<typename F, typename Xs, typename Ys>
using TL_zip_t = typename detail::zip_impl<F, Xs, Ys>::type;

template<> struct zip_shortest_with_algo<type_list_tag> {
   template<typename F, typename Xs, typename Ys>
   constexpr static auto apply(F, Xs, Ys) -> TL_zip_t<F, Xs, Ys> { return {}; }
};

template<> struct zip_shortest_algo<type_list_tag> {
   template<typename Xs, typename Ys>
   constexpr static auto apply(Xs xs, Ys ys) {
      return zip_shortest_with_algo<type_list_tag>::apply(
         [](auto l, auto r) { return make_type_pair(l, r); },
         xs,
         ys);
   }
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
