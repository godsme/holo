//
// Created by Darwin Yuan on 2020/8/28.
//

#include <catch.hpp>
#include <holo/types/tuple.h>

namespace {
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
}