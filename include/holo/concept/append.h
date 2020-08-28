//
// Created by Darwin Yuan on 2020/8/29.
//

#ifndef HOLO_APPEND_H
#define HOLO_APPEND_H

#include <holo/holo_ns.h>

HOLO_NS_BEGIN

template<typename Tag>
struct append_impl;

template<typename Tag>
struct prepend_impl;

template<typename Tag>
struct concat_impl;

HOLO_NS_END
#endif //HOLO_APPEND_H
