//
// Created by eugene on 1/7/17.
//

#pragma once

#include <set>
#include <string>
#include <algorithm>
#include <cassert>

#include "visitor.h"
#include "free_visitor.h"
#include "to_string_visitor.h"

struct substitute_visitor
    : visitor
{
    substitute_visitor(variable_ptr_t var, vertex_ptr_t new_expr)
        : _var(var->_name)
        , _new_expr(new_expr)
    {
        free_visitor visitor(_free_in_new);
        new_expr->accept(&visitor);
    }

    virtual void visit(application * app) override {
        app->_l_child->accept(this);
        vertex_ptr_t res_l = _res;

        app->_r_child->accept(this);
        vertex_ptr_t res_r = _res;

        _res = make_ptr<application>(res_l, res_r);
    }

    virtual void visit(lambda * lam) override {

        auto it = _binded.insert(lam->_var->_name);
        size_t cnt_var = _free_in_new.count(lam->_var->_name);
        _cnt_intersected += cnt_var;

        lam->_r_child->accept(this);
        _res = make_ptr<lambda>(lam->_var, _res);

        _binded.erase(it);
        _cnt_intersected -= cnt_var;
    }

    virtual void visit(variable * var) override {
        std::string const & var_name = var->_name;
        _res = make_ptr<variable>(var->_name);

        if (0 == _binded.count(var_name)) {
            if (var_name == _var) {
                if (0 == _cnt_intersected) {
                    _res = _new_expr;
                } else {
                    std::vector<std::string> intersection;
                    std::set_intersection(_free_in_new.begin(), _free_in_new.end(),
                                          _binded.begin(), _binded.end(),
                                          std::back_inserter(intersection));
                    assert(intersection.size() > 0);

                    std::cerr << "variable_grammar `" << intersection[0] << "` is not free for substitution" << std::endl;
                    std::cerr << "_var: " << _var << std::endl;
                    std::cerr << "_new_expr: " << *_new_expr << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    vertex_ptr_t _res;
    size_t _cnt_intersected = 0; // count of binded variables which exist in _free_in_new
    std::string _var;
    vertex_ptr_t   _new_expr;
    std::set<std::string> _free_in_new; // set of free variables in new expression_grammar, which will be substituted instead of _var
    std::multiset<std::string> _binded;
};
