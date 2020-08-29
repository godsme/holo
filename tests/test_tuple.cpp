//
// Created by Darwin Yuan on 2020/8/28.
//

#include <catch.hpp>
#include <holo/types/tuple/tuple.h>
#include <holo/holo.h>
#include <holo/algo/pipeline.h>
//#include <holo/types/sizeof_c.h>
//#include <holo/algo/reverse.h>
//#include <holo/algo/unique.h>
//#include <holo/algo/product.h>

namespace {
   TEST_CASE("construct an empty tuple") {
      static_assert(holo::tuple{} == holo::tuple{});
   }

   TEST_CASE("construct a tuple with literal") {
      constexpr auto xs = holo::tuple(holo::size_c<1>, holo::bool_c<true>);
      static_assert(xs == holo::tuple(holo::size_c<1>, holo::bool_c<true>));
      static_assert((xs == holo::tuple(holo::size_c<1>, holo::bool_c<true>)) == holo::bool_c<true>);
      static_assert(xs != holo::tuple(holo::size_c<2>, holo::bool_c<true>));
      static_assert((xs == holo::tuple(holo::size_c<2>, holo::bool_c<true>)) == holo::bool_c<false>);
      static_assert(xs != holo::tuple(holo::size_c<2>, holo::bool_c<true>));
      static_assert(xs != holo::tuple(holo::size_c<1>));
   }

   struct X {
      constexpr auto operator==(X const& rhs) const { return holo::true_c; }
      constexpr auto operator!=(X const& rhs) const { return holo::false_c; }
   };

   struct Y {
      constexpr auto operator==(Y const& rhs) const { return holo::true_c; }
      constexpr auto operator!=(Y const& rhs) const { return holo::false_c; }
   };

   TEST_CASE("construct a tuple with class") {
      constexpr auto xs = holo::tuple(X{}, Y{});
      constexpr auto ys = holo::tuple(X{}, Y{});
        static_assert(decltype(xs)::size == 2);
        static_assert(decltype(ys)::size == 2);
        static_assert(holo::get<0>(xs) == holo::get<0>(ys));
        static_assert(holo::get<1>(xs) == holo::get<1>(ys));
        static_assert(xs == ys);
        static_assert(xs != holo::tuple(Y{}, Y{}));
      static_assert(xs != holo::tuple(Y{}, X{}));
      static_assert(xs != holo::tuple(X{}));
      static_assert(xs != holo::tuple(Y{}));
      static_assert(xs != holo::tuple(1));
   }

   TEST_CASE("construct a tuple with literal & class") {
      constexpr auto xs = holo::tuple(holo::size_c<1>, X{});
      static_assert(xs == holo::tuple(holo::size_c<1>, X{}));
      static_assert((xs == holo::tuple(holo::size_c<1>, X{})) == holo::bool_c<true>);
      static_assert(xs != holo::tuple(holo::size_c<1>, Y{}));
      static_assert((xs == holo::tuple(holo::size_c<1>, Y{})) == holo::bool_c<false>);
   }

   TEST_CASE("get from a tuple") {
      constexpr auto xs = holo::tuple(1, X{});
      static_assert(holo::get<0>(xs) == 1);
      static_assert(holo::get<1>(xs) == X{});

      // should not compile
      //REQUIRE(holo::get<2>(xs) == 10);
   }

   TEST_CASE("get tuple size") {
      constexpr auto xs = holo::tuple(1, X{});
      static_assert(holo::tuple_size(xs) == 2);
   }

   TEST_CASE("tuple cat") {
      static_assert(holo::tuple_cat(holo::tuple(holo::size_c<1>, X{}), holo::tuple{holo::size_c<2>, Y{}}) == holo::tuple{holo::size_c<1>, X{}, holo::size_c<2>, Y{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, Y{}}, holo::tuple{Y{}, X{}}) == holo::tuple{X{}, Y{}, Y{}, X{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, Y{}}, holo::tuple{holo::size_c<1>, X{}}) == holo::tuple{X{}, Y{}, holo::size_c<1>, X{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, holo::size_c<2>}, holo::tuple{Y{}, X{}}) == holo::tuple{X{}, holo::size_c<2>, Y{}, X{}});
   }

   TEST_CASE("take from a tuple") {
      constexpr auto xs = holo::tuple(holo::size_c<2>, X{});
      static_assert(holo::take(holo::size_c<0>, xs) == holo::tuple{});
      static_assert(holo::take(holo::size_c<1>, xs) == holo::tuple{holo::size_c<2>});
      static_assert(holo::take(holo::size_c<2>, xs) == xs);
      //static_assert(holo::take<3>(xs) == xs);
   }

   TEST_CASE("drop from a tuple") {
      constexpr auto xs = holo::tuple(holo::size_c<2>, X{});
      static_assert(holo::drop(holo::size_c<2>, xs) == holo::tuple{});
      static_assert(holo::drop(holo::size_c<1>, xs) == holo::tuple{X{}});
      static_assert(holo::drop(holo::size_c<0>, xs) == xs);
      //static_assert(holo::drop<3>(xs) == xs);
   }

   TEST_CASE("get head") {
      constexpr auto xs = holo::tuple(2.3, X{});
      static_assert(holo::head(xs) == 2.3);
      //holo::head(holo::tuple{});
   }

   TEST_CASE("get tail") {
      constexpr auto xs = holo::tuple(2.3, X{}, holo::size_c<2>, Y{});
      static_assert(holo::tail(xs) == holo::tuple(X{}, holo::size_c<2>, Y{}));
      //holo::tail(holo::tuple{});
   }

   TEST_CASE("append a value") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>);
      static_assert(holo::append(Y{}, xs) == holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>, Y{}));
   }

   TEST_CASE("prepend a value") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>);
      static_assert(holo::prepend(Y{}, xs) == holo::tuple(Y{}, holo::size_c<3>, X{}, holo::size_c<2>));
   }

   TEST_CASE("concat") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>);
      static_assert(holo::concat(xs, holo::tuple{Y{}, holo::size_c<4>})
        == holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>, Y{}, holo::size_c<4>));
   }

   TEST_CASE("tuple contains") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>);
      static_assert(holo::contains(holo::size_c<2>, xs) == holo::true_c);
      static_assert(holo::contains(holo::size_c<1>, xs) == holo::false_c);
   }

   TEST_CASE("tuple_element") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(std::is_same_v<double, holo::tuple_element_t<0, decltype(xs)>>);
      static_assert(std::is_same_v<X, holo::tuple_element_t<1, decltype(xs)>>);
      static_assert(std::is_same_v<int, holo::tuple_element_t<2, decltype(xs)>>);
      //holo::tuple_element<3, decltype(xs)>;
   }

//   template<typename T> struct S;
   TEST_CASE("tuple filter") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>, X{});
      constexpr auto ys = holo::filter([](auto elem) {
         return holo::bool_c<!std::is_same_v<std::decay_t<decltype(elem)>, X>>;
      }, xs);
      static_assert(ys == holo::tuple{holo::size_c<3>, holo::size_c<2>});
   }

   TEST_CASE("tuple remove_if") {
      constexpr auto xs = holo::tuple(holo::size_c<3>, X{}, holo::size_c<2>, X{});
      constexpr auto ys = holo::remove_if([](auto elem) {
         return holo::bool_c<std::is_same_v<std::decay_t<decltype(elem)>, X>>;
      }, xs);
      static_assert(ys == holo::tuple{holo::size_c<3>, holo::size_c<2>});
   }

   TEST_CASE("tuple transform") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2, X{});
      constexpr auto ys = holo::transform([](auto elem) {
         if constexpr (std::is_arithmetic_v<decltype(elem)>) {
            return elem + 1;
         } else {
            return 0;
         }
      }, xs);

      REQUIRE(matches(ys, holo::tuple{3.3, 0, 3, 0}));
   }

   TEST_CASE("find if") {
      constexpr auto pred = [](auto elem) {
         if constexpr (holo::is_integral_const(elem)) {
            return elem > holo::size_c<10>;
         } else {
            return holo::false_c;
         }
      };

      constexpr auto xs = holo::tuple(2.3, X{}, 2, X{});
      static_assert(holo::is_nothing(holo::find_if(pred, xs)));
      static_assert(holo::size_c<11> == holo::find_if(pred,
              holo::tuple{holo::size_c<2>, X{}, 10.2, Y{}, holo::size_c<11>, X{}}));
   }

   TEST_CASE("tuple flatten") {
      constexpr auto list = holo::tuple(holo::type_c<int>, holo::type_c<char>,
                                        holo::tuple{holo::type_c<long>, holo::tuple(holo::type_c<char>), holo::type_c<float>},
                                        holo::type_c<double>, holo::type_c<long long>,
                                        holo::tuple(holo::type_c<short>, holo::tuple(holo::type_c<long double>), holo::type_c<float>));
      constexpr auto result = holo::flatten(list);
      static_assert(result == holo::tuple_t<int, char, long, char, float, double, long long, short, long double, float>);
   }

   TEST_CASE("tuple fold left") {
      constexpr auto result = holo::fold_left(holo::tuple{},
                                              [](auto const& acc, auto const& elem){
                                                 return holo::append(elem, acc);
                                              },
                                              holo::tuple_t<int, float, double>);

      static_assert(result == holo::tuple_t<int, float, double>);
   }

   TEST_CASE("tuple partition") {
      constexpr auto xs = holo::tuple_t<int, long long, char, float, short, double, bool, long double>;
      constexpr auto result = xs | holo::partition([](auto elem)  {
                                 return holo::sizeof_c<typename decltype(elem)::type> < holo::sizeof_c<size_t>;
                              });
      static_assert(result == holo::pair(holo::tuple_t<int, char, float, short, bool>, holo::tuple_t<long long, double, long double>));
   }

   TEST_CASE("tuple reverse") {
      static_assert(holo::tuple_t<float, double, int> == holo::reverse(holo::tuple_t<int, double, float>));
   }

   TEST_CASE("tuple unique") {
      constexpr auto result =
         holo::tuple_t<int, short, long long, short, char, int, long long, char, short> |
         holo::unique();

      static_assert(result == holo::tuple_t<int, short, long long, char>);
   }

   TEST_CASE("tuple product") {
      constexpr auto result = holo::product(
         holo::tuple_t<char, short, int>,
         holo::tuple_t<float, double>);

      static_assert(result == holo::tuple(holo::pair_t<char, float>, holo::pair_t<char, double>,
                                          holo::pair_t<short, float>, holo::pair_t<short, double>,
                                          holo::pair_t<int, float>, holo::pair_t<int, double>));
   }

   template<std::size_t Start, std::size_t ... Xn>
   auto make_sequence(std::index_sequence<Xn...>) -> std::index_sequence<Start+Xn...>;

   TEST_CASE("make_sequence") {
      using type = decltype(make_sequence<0>(std::make_index_sequence<0>{}));
      static_assert(std::is_same_v<std::index_sequence<>, type>);
   }
   TEST_CASE("tuple sort") {
      constexpr auto result = holo::sort([](auto l, auto r) {
                                 return holo::sizeof_c<typename decltype(l)::type> <
                                        holo::sizeof_c<typename decltype(r)::type>;
                              }, holo::tuple_t<int, long long, short, char>);

      static_assert(result == holo::tuple_t<char, short, int, long long>);
   }
}