//
// Created by eugene on 1/7/17.
//

#include <memory>
#include <sstream>
#include <set>
#include <substitute_visitor.h>

#include "hw3.h"
#include "to_string_visitor.h"

namespace hw3 {
    std::string main(std::string const &expr) {
        char const *f = expr.c_str();
        char const *l = f + expr.size();

        vertex_ptr_t expr_tree(parse(f, l));

        parser::skip('[', f);
        variable_ptr_t var(parser::variable_grammar(f));

        parser::skip(":=", f);
        vertex_ptr_t new_expr(parse(f, l));

        parser::skip(']', f);

        std::stringstream ss;
        to_string_visitor string_visitor(ss);

        vertex_ptr_t after_sub = substitute(expr_tree, var, new_expr);
        after_sub->accept(&string_visitor);

        return ss.str();
    }

    vertex_ptr_t substitute(vertex_ptr_t expr, variable_ptr_t var, vertex_ptr_t new_expr) {
        substitute_visitor visitor(var, new_expr);
        expr->accept(&visitor);

        return expr;
    }
} // namespace hw3
