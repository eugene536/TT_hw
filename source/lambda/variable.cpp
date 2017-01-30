//
// Created by eugene on 1/7/17.
//

#include "lambda/variable.h"
#include "lambda/visitor.h"

variable::variable(std::string name)
    : _name(name)
{}

void variable::accept(visitor * visitor) {
    visitor->visit(this);
}

variable * variable::deep_copy() const {
    return new variable(_name);
}
