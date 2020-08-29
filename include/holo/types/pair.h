//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_PAIR_H
#define HOLO_TUPLE_PAIR_H

#include <holo/types/tuple/tuple_t.h>
#include <type_traits>

HOLO_NS_BEGIN

struct pair_tag{};

template<typename X, typename Y>
struct pair {
   using tag_type = pair_tag;
   constexpr pair() = default;
   template<typename X1, typename Y1>
   constexpr pair(X1&& x, Y1&& y) : storage_{x, y} {}
   constexpr pair(pair const& rhs) = default;

   constexpr auto first() const {
      return get<0>(storage_);
   }

   constexpr auto second() const {
      return get<1>(storage_);
   }

//   template<std::size_t I>
//   constexpr auto get() const -> decltype(auto) {
//      return get<I>(storage_);
//   }

   template<typename  X2, typename Y2>
   constexpr auto operator==(pair<X2, Y2> const& rhs) const {
       return storage_ == rhs.storage_;
   }

    template<typename X1, typename Y1, typename  X2, typename Y2>
    constexpr auto operator!=(pair<X2, Y2> const& rhs) noexcept {
        return !operator==(rhs);
    }

   template<typename X1, typename Y1, typename ... Xs>
   constexpr auto operator==(tuple<Xs...> const& rhs) noexcept {
      return storage_ == rhs;
   }

private:
   using storage_type = tuple<X, Y>;
   storage_type storage_;
};

template<typename X, typename Y>
pair(X&&, Y&&) -> pair<std::decay_t<X>, std::decay_t<Y>>;

//
//template<typename X1, typename Y1, typename ... Xs>
//constexpr auto operator!=(pair<X1, Y1> const& lhs, tuple<Xs...> const& rhs) noexcept {
//   return !operator==(lhs, rhs);
//}
//
//template<typename ... Xs, typename  X2, typename Y2>
//constexpr auto operator!=(tuple<Xs...> const& lhs, pair<X2, Y2> const& rhs) noexcept {
//   return !operator==(lhs, rhs);
//}

template<> struct first_algo<pair_tag> {
   template<typename Pair>
   constexpr static auto apply(Pair const& p) {
      return p.first();
   }
};

template<> struct second_algo<pair_tag> {
   template<typename Pair>
   constexpr static auto apply(Pair const& p) {
      return p.second();
   }
};

template<typename FIRST, typename SECOND>
constexpr pair<type_c_t<FIRST>, type_c_t<SECOND>> pair_t{};

HOLO_NS_END

#endif //HOLO_TUPLE_PAIR_H
