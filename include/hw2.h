//
// Created by eugene on 1/7/17.
//

#pragma once

#include <set>

#include "vertex.h"

namespace hw2 {
    std::string main(std::string const & expr);

    std::set<std::string> get_free_vars(vertex_ptr_t vertex);
}

