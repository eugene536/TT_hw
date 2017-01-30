//
// Created by eugene on 1/7/17.
//

#pragma once

#include "lambda/pointer.h"

struct vertex {
    virtual ~vertex() {}
    virtual void accept(struct visitor * visitor) = 0;

    ptr<vertex> deep_copy_ptr() {
        return ptr<vertex>(deep_copy());
    }

    virtual vertex * deep_copy() const = 0;
};

typedef ptr<vertex> vertex_ptr_t;

std::string generate_var();
void clear_var_generator();
