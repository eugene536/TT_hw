//
// Created by eugene on 1/7/17.
//

#pragma once

#include <memory>

template<typename T>
using ptr = std::shared_ptr<T>;

struct vertex {
    virtual ~vertex() {}
    virtual void accept(struct visitor * visitor) = 0;

    ptr<vertex> deep_copy_ptr() {
        return ptr<vertex>(deep_copy());
    }

    virtual vertex * deep_copy() const = 0;
};

typedef ptr<vertex> vertex_ptr_t;

template<typename RetT, typename ...Args>
ptr<RetT> make_ptr(Args&&... args) {
    return std::make_shared<RetT>(std::forward<Args>(args)...);
}


std::string generate_var();
void clear_var_generator();
