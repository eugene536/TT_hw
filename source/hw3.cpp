//
// Created by eugene on 1/7/17.
//

#include <memory>
#include <sstream>
#include <set>
#include <lambda/substitute_visitor.h>

namespace hw3 {
    std::string main(std::string const &expr) {
        char const *f = expr.c_str();
        char const *l = f + expr.size();

        vertex_ptr_t expr_tree(parse(f, l));

        lambda_parser::skip('[', f);
        variable_ptr_t var(lambda_parser::variable_grammar(f));

        lambda_parser::skip(":=", f);
        vertex_ptr_t new_expr(parse(f, l));

        lambda_parser::skip(']', f);

        std::stringstream ss;
        to_string_visitor string_visitor(ss);

        vertex_ptr_t after_sub = substitute(expr_tree, var, new_expr);
        after_sub->accept(&string_visitor);

        return ss.str();
    }

    vertex_ptr_t substitute(vertex_ptr_t expr, variable_ptr_t var, vertex_ptr_t new_expr) {
//        std::cerr << "substitute:"  << std::endl;
//        std::cerr << "  expr: " << *expr << std::endl;
//        std::cerr << "  var: " << *var << std::endl;
//        std::cerr << "  new_expr: " << *new_expr << std::endl;

        substitute_visitor visitor(var, expr, new_expr);
        expr->accept(&visitor);

//        std::cerr << "after subst: " << *visitor._res << std::endl;
        return visitor._res;
    }
} // namespace hw3
