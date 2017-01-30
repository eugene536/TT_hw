//
// Created by eugene on 1/30/17.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "lambda/pointer.h"

namespace equation {
    struct vertex {
        vertex();

        explicit vertex(std::string const & name);

        bool is_variable() const;

        std::string to_string() const;

        std::string _name;
        std::vector<ptr<vertex>> _children;
    };

    typedef ptr<vertex> vertex_ptr_t;

    std::ostream& operator<<(std::ostream& out, vertex const & ver);
}