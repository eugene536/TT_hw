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
    struct vertex;

    typedef ptr<equation::vertex> vertex_ptr_t;

    struct vertex {
        vertex();

        explicit vertex(std::string const & name);

        template<typename...Args>
        vertex(std::string const & name, Args&&...children)
            : _name(name)
            , _children{children...}
        {}

        bool is_variable() const;

        bool contains_var(std::string const & var) const;

        bool substitute(std::string const & var, vertex_ptr_t const & expr);

        vertex_ptr_t deep_copy() const;

        std::string to_string() const;

        std::string to_suffix_string() const;

        bool operator==(vertex const & rhs) const;

        bool operator!=(vertex const & rhs) const;

        std::string _name;
        std::vector<vertex_ptr_t> _children;
    };

    std::ostream& operator<<(std::ostream& out, vertex const & ver);
}