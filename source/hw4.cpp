//
// Created by eugene on 1/21/17.
//

#include <memory>
#include <cassert>
#include <sstream>

#include "to_string_visitor.h"

#include "hw3.h"
#include "hw4.h"

namespace hw4 {

    vertex_ptr_t to_head_normal(vertex_ptr_t expr) {
        vertex_ptr_t res = expr;

        if (application_ptr_t app = std::dynamic_pointer_cast<application>(expr)) {
            app->_l_child = to_head_normal(app->_l_child);
            vertex_ptr_t left = app->_l_child;
            vertex_ptr_t right = app->_r_child;

            if (lambda_ptr_t left_lam = std::dynamic_pointer_cast<lambda>(left)) {
                vertex_ptr_t subst = hw3::substitute(left_lam->_r_child, left_lam->_var, right);
                res = to_head_normal(subst);
            } else {
                app->_r_child = to_normal(right);
            }
        }

        return res;
    }

    vertex_ptr_t to_normal(vertex_ptr_t expr) {
        vertex_ptr_t res = expr;

        if (application_ptr_t app = std::dynamic_pointer_cast<application>(expr)) {
            app->_l_child = to_head_normal(app->_l_child);
            vertex_ptr_t left = app->_l_child;
            vertex_ptr_t right = app->_r_child;

            if (lambda_ptr_t left_lam = std::dynamic_pointer_cast<lambda>(left)) {
                vertex_ptr_t subst = hw3::substitute(left_lam->_r_child, left_lam->_var, right);
                res = to_normal(subst);
            } else {
                app->_r_child = to_normal(app->_r_child);
            }
        } else if (lambda_ptr_t lam = std::dynamic_pointer_cast<lambda>(expr)) {
            lam->_r_child = to_normal(lam->_r_child);
        } else {
            assert(std::dynamic_pointer_cast<variable>(expr));
        }

        return res;
    }

    std::string main(std::string const &expr) {
        char const *f = expr.c_str();
        char const *l = f + expr.size();

        vertex_ptr_t expr_tree = parse(f, l);

        if (f != l) {
            std::cerr << "hw2:: f != l:: " << std::string(f, l) << std::endl;
        }

        std::stringstream ss;
        to_string_visitor string_visitor(ss);

        vertex_ptr_t normal = to_normal(expr_tree);
        normal->accept(&string_visitor);

        return ss.str();
    }
} // namespace hw4
