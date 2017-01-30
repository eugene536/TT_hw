//
// Created by eugene on 1/30/17.
//

#pragma once

#include "equation/vertex.h"

namespace equation {
    std::pair<vertex_ptr_t, vertex_ptr_t> parse(std::string const & expr);
} // namespace equation
