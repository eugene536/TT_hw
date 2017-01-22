//
// Created by eugene on 1/7/17.
//

#include "application.h"
#include "visitor.h"

application::application(vertex_ptr_t l_child, vertex_ptr_t r_child)
        : _l_child(l_child)
        , _r_child(r_child)
{}

void application::accept(visitor * visitor) {
    visitor->visit(this);
}

application * application::deep_copy() const {
    return new application(_l_child->deep_copy_ptr(), _r_child->deep_copy_ptr());
}

