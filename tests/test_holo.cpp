//
// Created by Darwin Yuan on 2020/8/26.
//

#include <catch.hpp>
#include <holo/algo/fold_left.h>
#include <holo/types/type_list/type_list.h>
#include <holo/algo/find_if.h>
#include <holo/algo/transform.h>
#include <holo/algo/filter.h>
#include <holo/algo/contains.h>
#include <holo/algo/append.h>
#include <holo/algo/prepend.h>
#include <holo/algo/concat.h>
#include <holo/algo/remove_if.h>
#include <holo/algo/reverse.h>
#include <holo/algo/head.h>
#include <holo/algo/tail.h>
#include <holo/algo/partition.h>
#include <holo/algo/sort.h>
#include <holo/types/integral_constant/sizeof_c.h>
#include <holo/algo/unique.h>
#include <holo/algo/flatten.h>
#include <holo/algo/product.h>
#include <holo/algo/zip.h>
#include <holo/algo/group.h>
#include <holo/algo/any_of.h>
#include <holo/algo/all_of.h>
#include <holo/algo/none_of.h>

namespace {
   TEST_CASE("holo fold left") {
      constexpr auto result = holo::type_list_t<int, float, double> |
         holo::fold_left(holo::type_list_t<>,
                [](auto const& acc, auto const& elem){
                   return holo::append(elem, acc);
                });

      static_assert(result == holo::type_list_t<int, float, double>);
   }

   TEST_CASE("holo fold left 1") {
      constexpr auto result =
         holo::type_list<holo::type_list<int>, holo::type_list<float>, holo::type_list<double>>{} |
         holo::fold_left_1([](auto const& acc, auto const& elem){
            return holo::concat(acc, elem); });

      static_assert(result == holo::type_list<int, float, double>{});
   }

   template<int VALUE>
   struct value_holder { constexpr static auto value = VALUE; };

   TEST_CASE("holo fold left 2") {
      constexpr auto result = holo::type_list_t<value_holder<1>, value_holder<2>, value_holder<3>> |
         holo::fold_left(0,
             [](auto const& acc, auto elem){ return decltype(elem)::type::value + acc; });

      REQUIRE(result == 6);
   }

   template<typename T> struct S;

   TEST_CASE("Is_Pred_Satisfied") {
      auto l = [](auto elem) {
            return elem == holo::type_c<double>;
         };
      static_assert(holo::detail::Is_Pred_Satisfied<decltype(l), holo::type_c_t<double>>);
      static_assert(!holo::detail::Is_Pred_Satisfied<decltype(l), holo::type_c_t<int>>);

   }

   TEST_CASE("holo find if") {
      constexpr auto result = holo::type_list_t<int, double, float> |
         holo::find_if([](auto elem) {
            return elem == holo::type_c<double>;
         });

      static_assert(result != holo::nothing, "");
      static_assert(result == holo::type_c<double>);
   }

   TEST_CASE("holo type_list contains") {
      constexpr auto result = holo::type_list_t<int, double, float> |
                              holo::contains(holo::type_c<double>);

      static_assert(result);
   }

   template <typename T> struct w{};
   TEST_CASE("holo transform") {
      constexpr auto result = holo::type_list_t<int, double, float> | holo::transform(
         [](auto elem) constexpr {
            return holo::type_c<w<typename decltype(elem)::type>>;
         });

      static_assert(result == holo::type_list_t<w<int>, w<double>, w<float>>);
   }

   TEST_CASE("holo filter") {
      constexpr auto result = holo::type_list_t<int, double, float> |
         holo::filter(
         [](auto elem) constexpr {
            return elem != holo::type_c<double>;
         });

      static_assert(result == holo::type_list_t<int, float>);
   }

   TEST_CASE("holo remove_if") {
      constexpr auto result = holo::type_list_t<int, double, float> |
         holo::remove_if([](auto elem) constexpr {
            return elem == holo::type_c<double>;
         });

      static_assert(result == holo::type_list_t<int, float>);
   }

   TEST_CASE("contains") {
      static_assert(holo::contains(holo::type_c<int>, holo::type_list_t<int, double, float>));
      static_assert(!holo::contains(holo::type_c<long>, holo::type_list_t<int, double, float>));
   }

   TEST_CASE("append") {
      static_assert(holo::type_list_t<int, double, float, long> == holo::append(holo::type_c<long>, holo::type_list_t<int, double, float>));
      static_assert(holo::type_list_t<long, int, double, float> == holo::prepend(holo::type_c<long>, holo::type_list_t<int, double, float>));
      static_assert(holo::type_list_t<long, char, int, double, float> == holo::concat(holo::type_list_t<long, char>, holo::type_list_t<int, double, float>));
   }

   TEST_CASE("reverse") {
      static_assert(holo::type_list_t<float, double, int> == holo::reverse(holo::type_list_t<int, double, float>));
   }

   TEST_CASE("head") {
      static_assert(holo::type_c<int> == holo::head(holo::type_list_t<int, double, float>));
      static_assert(holo::type_list_t<double, float> == holo::tail(holo::type_list_t<int, double, float>));
   }

   template <typename T> struct S;
   TEST_CASE("partition") {
      constexpr auto result = holo::type_list_t<int, long long, char, float, short, double, bool, long double> |
         holo::partition([](auto elem)  {
            return holo::sizeof_c<typename std::decay_t<decltype(elem)>::type> < holo::sizeof_c<size_t>;
         });

      static_assert(result == holo::make_type_pair(holo::type_list_t<int, char, float, short, bool>, holo::type_list_t<long long, double, long double>));
   }

   TEST_CASE("sort") {
      constexpr auto result = holo::type_list_t<long double, int, long long, bool, short, char> |
         holo::sort([](auto l, auto r) {
            return holo::sizeof_c<typename std::decay_t<decltype(l)>::type> <
                   holo::sizeof_c<typename std::decay_t<decltype(r)>::type>;
         });

      static_assert(result == holo::type_list_t<bool, char, short, int, long long, long double>);
   }

   TEST_CASE("unique") {
      constexpr auto result =
         holo::type_list_t<int, short, long long, short, char, int, long long, char, short> |
         holo::unique();

      static_assert(result == holo::type_list_t<int, short, long long, char>);
   }

    template<typename T> struct S;

   TEST_CASE("flatten") {
      constexpr auto xs =
         holo::make_type_list(holo::type_c<int>, holo::type_c<char>,
            holo::make_type_list(holo::type_c<long>, holo::make_type_list(holo::type_c<char>), holo::type_c<float>),
            holo::type_c<double>, holo::type_c<long long>,
            holo::make_type_list(holo::type_c<short>, holo::make_type_list(holo::type_c<long double>), holo::type_c<float>));

      constexpr auto result = holo::flatten(xs);
      static_assert(result == holo::type_list_t<int, char, long, char, float, double, long long, short, long double, float>);
   }

   TEST_CASE("product") {
      constexpr auto result = holo::product(
         holo::type_list_t<char, short, int>,
         holo::type_list_t<float, double>);

      static_assert(result == holo::make_type_list(
         holo::type_pair_t<char, float>, holo::type_pair_t<char, double>,
         holo::type_pair_t<short, float>, holo::type_pair_t<short, double>,
         holo::type_pair_t<int, float>, holo::type_pair_t<int, double>));
   }

   TEST_CASE("zip") {
      constexpr auto result = holo::zip(
         holo::type_list_t<char, short, int>,
         holo::type_list_t<float, double, long>);

      static_assert(result == holo::make_type_list(
         holo::type_pair_t<char, float>,
         holo::type_pair_t<short, double>,
         holo::type_pair_t<int, long>));
   }

   TEST_CASE("zip with") {
      constexpr auto result = holo::zip_with([](auto l, auto r){
            return holo::sizeof_type(l) > holo::sizeof_type(r);
         },
         holo::type_list_t<char, short, long>,
         holo::type_list_t<float, double, int>);

      static_assert(result == holo::bool_list_t<false, false, true>);
   }

   TEST_CASE("zip shortest") {
      constexpr auto result = holo::zip_shortest(
         holo::type_list_t<char, short, int>,
         holo::type_list_t<float, double>);

      static_assert(result == holo::make_type_list(
         holo::type_pair_t<char, float>,
         holo::type_pair_t<short, double>));
   }

   TEST_CASE("zip shortest with") {
      constexpr auto result = holo::zip_shortest_with(
         [](auto l, auto r){
            return holo::sizeof_type(l) > holo::sizeof_type(r); },
         holo::type_list_t<char, long>,
         holo::type_list_t<float, short, int>);

      static_assert(result == holo::bool_list_t<false, true>);
   }

   TEST_CASE("group") {
      constexpr auto result = holo::type_list_t<int, char, long, char, float, double, long, double, long, float>
         | holo::group();

      constexpr auto expected = holo::make_type_list(
         holo::type_list_t<int>,
         holo::type_list_t<char, char>,
         holo::type_list_t<long, long, long>,
         holo::type_list_t<float, float>,
         holo::type_list_t<double, double>);

      static_assert(result == expected);
   }

   TEST_CASE("group by") {
      constexpr auto result = holo::type_list_t<int, char, long, char, bool, double, uint64_t, uint32_t, float, bool>
                              | holo::group_by([](auto l, auto r) {
                                 return holo::sizeof_type(l) == holo::sizeof_type(r);
                              });

      constexpr auto expected = holo::make_type_list(
         holo::type_list_t<int, uint32_t, float>,
         holo::type_list_t<char, char, bool, bool>,
         holo::type_list_t<long, double, uint64_t>);

      static_assert(result == expected);
   }

   TEST_CASE("any of") {
      constexpr auto result = holo::type_list_t<int, char, long, char, bool, double, uint64_t, uint32_t, float, bool>
                              | holo::any_of([](auto l) {
               return holo::sizeof_type(l) == holo::size_c<1>;
      });

      static_assert(result);
   }

   TEST_CASE("all of") {
      constexpr auto list = holo::type_list_t<int, char, long, char, bool, double, uint64_t, uint32_t, float, bool>;
      static_assert(!holo::all_of([](auto l) {
               return holo::sizeof_type(l) == holo::size_c<1>;
            }, list));

      static_assert(holo::all_of([](auto l) {
         return holo::sizeof_type(l) <= holo::size_c<8>;
      }, list));
   }

   TEST_CASE("none of") {
      constexpr auto list = holo::type_list_t<int, char, long, char, bool, double, uint64_t, uint32_t, float, bool>;
      static_assert(holo::none_of([](auto l) {
         return holo::sizeof_type(l) > holo::size_c<8>;
      }, list));

      static_assert(!holo::none_of([](auto l) {
         return holo::sizeof_type(l) == holo::size_c<1>;
      }, list));
   }
}