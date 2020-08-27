//
// Created by godsme on 8/27/20.
//

#ifndef HOLO_PARTIAL_APPLY_H
#define HOLO_PARTIAL_APPLY_H

#include <holo/types/tuple.h>

HOLO_NS_BEGIN

template<typename F, typename... Args>
constexpr auto partial_apply(F&& f, Args&& ... args) {
   return [=](auto ... rest) {
      return f(args..., rest...);
   };
}

#define __return_invoke(...) \
return [](auto stream) { return invoke<__VA_ARGS__>(stream); }

#define __return_invoke_0() \
return [](auto stream) { return invoke(stream); }

HOLO_NS_END

#endif //HOLO_PARTIAL_APPLY_H
