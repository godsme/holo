//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TUPLE_FILTER_H
#define HOLO_TUPLE_FILTER_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/non_comparable.h>
#include <holo/algo/detail/pred.h>
#include <array>

HOLO_NS_BEGIN

namespace detail {
   template<typename T>
   constexpr auto count(T const* begin, T const* end, T value) -> std::size_t {
      std::size_t c = 0;
      for(auto* i = begin; i != end; i++) {
         if(*i == value) ++c;
      }
      return c;
   }

   template<bool ... B>
   struct tuple_filter_helper {
      constexpr static auto compute() {
         constexpr bool result[] = { B..., false};
         constexpr std::size_t size = count(result, result + sizeof...(B), true);
         std::array<std::size_t, size> indices{};
         std::size_t* keep = &indices[0];
         for(size_t i=0; i<sizeof...(B); i++) {
            if(result[i]) *keep++ = i;
         }
         return indices;
      }
      constexpr static auto Indices = compute();
   };
}

template<>
struct filter_algo<tuple_tag> {
private:
   template<typename Helper, std::size_t ... Yn, typename Xs>
   constexpr static auto make_result(Xs const& xs, std::index_sequence<Yn...>) {
      return tuple{get<Helper::Indices[Yn]>(xs)...};
   }

public:
   template<typename PRED, typename ... Xs>
   constexpr static auto apply(PRED const& pred, tuple<Xs...> const& xs) {
      using Helper = detail::tuple_filter_helper<detail::Is_Pred_Satisfied<PRED, Xs>...>;
      return make_result<Helper>(xs, std::make_index_sequence<Helper::Indices.size()>{});
   }
};

HOLO_NS_END

#endif //HOLO_TUPLE_FILTER_H
