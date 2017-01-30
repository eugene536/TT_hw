//
// Created by eugene on 1/30/17.
//

#pragma once

#include "equation/vertex.h"

namespace equation {
    typedef std::pair<vertex_ptr_t, vertex_ptr_t> equation_t;
    typedef std::vector<equation_t> equation_system_t;

    equation_t parse(std::string const & expr);

    equation_system_t solve(equation_system_t const & system);
} // namespace equation
