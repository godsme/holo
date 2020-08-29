//
// Created by Darwin Yuan on 2020/8/28.
//

#include <catch.hpp>
#include <holo/types/tuple/tuple.h>
#include <holo/algo/append.h>
#include <holo/algo/prepend.h>
#include <holo/algo/concat.h>
#include <holo/algo/contains.h>
#include <holo/algo/filter.h>
#include <holo/algo/remove_if.h>
#include <holo/algo/find_if.h>
#include <holo/algo/transform.h>
#include <holo/algo/flatten.h>

namespace {
   TEST_CASE("construct an empty tuple") {
      static_assert(holo::tuple{} == holo::tuple{});
   }

   TEST_CASE("construct a tuple with literal") {
      constexpr auto xs = holo::tuple(1, 2.0);
      static_assert(xs == holo::tuple(1, 2.0));
      static_assert((xs == holo::tuple(1, 2.0)) == holo::bool_c<true>);
      static_assert(xs != holo::tuple(1.0, 2.0));
      static_assert((xs == holo::tuple(1.0, 2.0)) == holo::bool_c<false>);
      static_assert(xs != holo::tuple(1, 2));
      static_assert(xs != holo::tuple(1));
   }

   struct X {
      constexpr auto operator==(X const& rhs) const { return true; }
      constexpr auto operator!=(X const& rhs) const { return false; }
   };

   struct Y {
      constexpr auto operator==(Y const& rhs) const { return true; }
      constexpr auto operator!=(Y const& rhs) const { return false; }
   };

   TEST_CASE("construct a tuple with class") {
      constexpr auto xs = holo::tuple(X{}, Y{});
      static_assert(xs == holo::tuple(X{}, Y{}));
      static_assert(xs != holo::tuple(Y{}, Y{}));
      static_assert(xs != holo::tuple(Y{}, X{}));
      static_assert(xs != holo::tuple(X{}));
      static_assert(xs != holo::tuple(Y{}));
      static_assert(xs != holo::tuple(1));
   }

   TEST_CASE("construct a tuple with literal & class") {
      constexpr auto xs = holo::tuple(1, X{});
      static_assert(xs == holo::tuple(1, X{}));
      static_assert((xs == holo::tuple(1, X{})) == holo::bool_c<true>);
      static_assert(xs != holo::tuple(1, Y{}));
      static_assert((xs == holo::tuple(1, Y{})) == holo::bool_c<false>);
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
      static_assert(holo::tuple_cat(holo::tuple(1, X{}), holo::tuple{2.0, Y{}}) == holo::tuple{1, X{}, 2.0, Y{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, Y{}}, holo::tuple{Y{}, X{}}) == holo::tuple{X{}, Y{}, Y{}, X{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, Y{}}, holo::tuple{1, X{}}) == holo::tuple{X{}, Y{}, 1, X{}});
      static_assert(holo::tuple_cat(holo::tuple{X{}, 2.0}, holo::tuple{Y{}, X{}}) == holo::tuple{X{}, 2.0, Y{}, X{}});
   }

   TEST_CASE("take from a tuple") {
      constexpr auto xs = holo::tuple(2.3, X{});
      static_assert(holo::take<0>(xs) == holo::tuple{});
      static_assert(holo::take<1>(xs) == holo::tuple{2.3});
      static_assert(holo::take<2>(xs) == xs);
      //static_assert(holo::take<3>(xs) == xs);
   }

   TEST_CASE("drop from a tuple") {
      constexpr auto xs = holo::tuple(2.3, X{});
      static_assert(holo::drop<2>(xs) == holo::tuple{});
      static_assert(holo::drop<1>(xs) == holo::tuple{X{}});
      static_assert(holo::drop<0>(xs) == xs);
      //static_assert(holo::drop<3>(xs) == xs);
   }

   TEST_CASE("get head") {
      constexpr auto xs = holo::tuple(2.3, X{});
      static_assert(holo::head(xs) == 2.3);
      //holo::head(holo::tuple{});
   }

   TEST_CASE("get tail") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2, Y{});
      static_assert(holo::tail(xs) == holo::tuple(X{}, 2, Y{}));
      //holo::tail(holo::tuple{});
   }

   TEST_CASE("append a value") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(holo::append(Y{}, xs) == holo::tuple(2.3, X{}, 2, Y{}));
   }

   TEST_CASE("prepend a value") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(holo::prepend(Y{}, xs) == holo::tuple(Y{}, 2.3, X{}, 2));
   }

   TEST_CASE("concat") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(holo::concat(xs, holo::tuple{Y{}, 4}) == holo::tuple(2.3, X{}, 2, Y{}, 4));
   }

   TEST_CASE("tuple contains") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(holo::contains(2, xs) == holo::true_type{});
   }

   TEST_CASE("tuple_element") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2);
      static_assert(std::is_same_v<double, holo::tuple_element_t<0, decltype(xs)>>);
      static_assert(std::is_same_v<X, holo::tuple_element_t<1, decltype(xs)>>);
      static_assert(std::is_same_v<int, holo::tuple_element_t<2, decltype(xs)>>);
      //holo::tuple_element<3, decltype(xs)>;
   }

   template<typename T> struct S;
   TEST_CASE("tuple filter") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2, X{});
      constexpr auto ys = holo::filter([](auto elem) {
         return holo::bool_c<!std::is_same_v<std::decay_t<decltype(elem)>, X>>;
      }, xs);
      static_assert(ys == holo::tuple{2.3, 3});
   }

   template<typename T> struct S;
   TEST_CASE("tuple remove_if") {
      constexpr auto xs = holo::tuple(2.3, X{}, 2, X{});
      constexpr auto ys = holo::remove_if([](auto elem) {
         return holo::bool_c<std::is_same_v<std::decay_t<decltype(elem)>, X>>;
      }, xs);
      static_assert(ys == holo::tuple{2.3, 3});
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

      static_assert(ys == holo::tuple{3.3, 0, 4, 0});
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

   TEST_CASE("flatten") {
      constexpr auto list = holo::tuple(holo::type_c<int>, holo::type_c<char>,
                                        holo::tuple{holo::type_c<long>, holo::tuple(holo::type_c<char>), holo::type_c<float>},
                                        holo::type_c<double>, holo::type_c<long long>,
                                        holo::tuple(holo::type_c<short>, holo::tuple(holo::type_c<long double>), holo::type_c<float>));
      constexpr auto result = holo::flatten(list);
      static_assert(result == holo::tuple_t<int, char, long, char, float, double, long long, short, long double, float>);
   }
}