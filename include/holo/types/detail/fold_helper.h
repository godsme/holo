//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_FOLD_HELPER_H
#define HOLO_FOLD_HELPER_H

#include <holo/holo_ns.h>
#include <utility>

HOLO_NS_BEGIN namespace detail {

template <typename T, typename F>
struct fold_helper {
   constexpr fold_helper(T result, F& f) : result_(result), f_(f) {}

   template<typename ELEM>
   constexpr auto operator<<(ELEM&& elem) const {
      auto result = f_(result_, elem);
      return fold_helper<decltype(result), F>{result, f_};
   }

   constexpr auto operator()() const -> T const& { return result_; }

   T result_;
   F& f_;
};

} HOLO_NS_END

#endif //HOLO_FOLD_HELPER_H
