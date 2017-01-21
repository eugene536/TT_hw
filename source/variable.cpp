//
// Created by eugene on 1/7/17.
//

#include "variable.h"
#include "visitor.h"

variable::variable(std::string name)
    : _name(name)
{}

void variable::accept(visitor * visitor) {
    visitor->visit(this);
}
