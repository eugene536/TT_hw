//
// Created by eugene on 1/7/17.
//

#pragma once

#include <string>

#include "parser.h"

namespace hw3 {
    std::string main(std::string const &expr);

    vertex_ptr_t substitute(vertex_ptr_t expr, variable_ptr_t var, vertex_ptr_t new_expr);
}
