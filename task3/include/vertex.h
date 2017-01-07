//
// Created by eugene on 1/7/17.
//

#pragma once

#include <memory>

struct vertex {
    virtual ~vertex() {}
    virtual void accept(struct visitor * visitor) = 0;
};

template<typename T>
using ptr = std::shared_ptr<T>;

typedef ptr<vertex> vertex_ptr_t;

template<typename RetT, typename ...Args>
ptr<RetT> make_ptr(Args&&... args) {
    return std::make_shared<RetT>(std::forward<Args>(args)...);
}

