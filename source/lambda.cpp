//
// Created by eugene on 1/7/17.
//

#include "lambda.h"
#include "visitor.h"

lambda::lambda(variable_ptr_t var, vertex_ptr_t r_child)
        : _var(var)
        , _r_child(r_child)
{}

void lambda::accept(visitor * visitor) {
    visitor->visit(this);
}
