//
// Created by eugene on 1/7/17.
//

#include "lambda/lambda.h"
#include "lambda/visitor.h"

lambda::lambda(variable_ptr_t var, vertex_ptr_t r_child)
        : _var(var)
        , _r_child(r_child)
{}

void lambda::accept(visitor * visitor) {
    visitor->visit(this);
}

lambda * lambda::deep_copy() const {
    return new lambda(ptr<variable>(_var->deep_copy()), _r_child->deep_copy_ptr());
}
