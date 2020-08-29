//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_FILTER_RESULT_H
#define HOLO_FILTER_RESULT_H

#include <holo/types/tuple/tuple_t.h>
#include <holo/types/non_comparable.h>
#include <holo/algo/detail/pred.h>
#include <array>

HOLO_NS_BEGIN namespace detail {

template<typename T>
constexpr auto count(T const* begin, T const* end, T value) -> std::size_t {
   std::size_t c = 0;
   for(auto* i = begin; i != end; i++) {
      if(*i == value) ++c;
   }
   return c;
}

template<bool ... B>
struct filter_indices {
   constexpr static auto compute() {
      constexpr bool result[] = { B..., false};
      constexpr std::size_t N = count(result, result + sizeof...(B), true);
      std::array<std::size_t, N> indices{};
      std::size_t* keep = &indices[0];
      for(size_t i=0; i<sizeof...(B); i++) {
         if(result[i]) *keep++ = i;
      }
      return indices;
   }
   constexpr static auto cached_indices = compute();
};

template<typename Indices, std::size_t ... Yn, typename Xs>
constexpr auto filter_result(Xs const& xs, std::index_sequence<Yn...>) {
   return tuple{get<Indices::cached_indices[Yn]>(xs)...};
}

} HOLO_NS_END

#endif //HOLO_FILTER_RESULT_H
