//
// Created by eugene on 1/7/17.
//

#pragma once

#include <memory>

#include "vertex.h"

struct application
    : vertex
{
    application(vertex_ptr_t l_child, vertex_ptr_t r_child);

    virtual void accept(struct visitor * visitor);
    application * deep_copy() const override;

    vertex_ptr_t _l_child;
    vertex_ptr_t _r_child;
};

typedef ptr<application> application_ptr_t;

