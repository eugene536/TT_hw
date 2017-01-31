//
// Created by eugene on 1/30/17.
//

#pragma once

#include <memory>

#ifndef DEBUG
template<typename T>
using ptr = T*;

template<typename RetT, typename ...Args>
ptr<RetT> make_ptr(Args&&... args) {
    return new RetT(std::forward<Args>(args)...);
}

template<typename U, typename T>
ptr<U> my_dynamic_cast(ptr<T> p) {
    return dynamic_cast<ptr<U>>(p);
}

#else

template<typename T>
using ptr = std::shared_ptr<T>;

template<typename RetT, typename ...Args>
ptr<RetT> make_ptr(Args&&... args) {
    return std::make_shared<RetT>(std::forward<Args>(args)...);
}

template<typename U, typename T>
ptr<U> my_dynamic_cast(ptr<T> p) {
    return std::dynamic_pointer_cast<U>(p);
}

#endif
