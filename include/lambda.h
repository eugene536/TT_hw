//
// Created by eugene on 1/7/17.
//

#pragma once

#include <memory>

#include "vertex.h"
#include "variable.h"

struct lambda
        : vertex
{
    lambda(variable_ptr_t var, vertex_ptr_t r_child);

    virtual void accept(struct visitor * visitor);
    virtual lambda * deep_copy() const override;

    variable_ptr_t _var;
    vertex_ptr_t   _r_child;
};

typedef ptr<lambda> lambda_ptr_t;



