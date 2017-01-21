//
// Created by eugene on 1/21/17.
//

#pragma once

#include <string>

#include "parser.h"

namespace hw4 {
    std::string main(std::string const &expr);

    vertex_ptr_t to_normal(vertex_ptr_t expr);
} // namespace hw4
