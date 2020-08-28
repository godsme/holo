//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_TAG_OF_H
#define HOLO_TAG_OF_H

#include <holo/holo_ns.h>

HOLO_NS_BEGIN

template<typename T>
struct tag_of {
   using type = typename std::decay_t<T>::tag_type;
};

HOLO_NS_END

#endif //HOLO_TAG_OF_H
