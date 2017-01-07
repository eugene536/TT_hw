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
        _cur_par = &app->_l_child;
        app->_l_child->accept(this);

        _cur_par = &app->_r_child;
        app->_r_child->accept(this);
    }

    virtual void visit(lambda * lam) override {

        auto it = _binded.insert(lam->_var->_name);
        size_t cnt_var = _free_in_new.count(lam->_var->_name);
        _cnt_intersected += cnt_var;

        _cur_par = &lam->_r_child;
        lam->_r_child->accept(this);
        _binded.erase(it);

        _cnt_intersected -= cnt_var;
    }

    virtual void visit(variable * var) override {
        std::string const & var_name = var->_name;

        if (0 == _binded.count(var_name)) {
            if (var_name == _var) {
                if (0 == _cnt_intersected) {
                    *_cur_par = _new_expr;
                } else {
                    std::vector<std::string> intersection;
                    std::set_intersection(_free_in_new.begin(), _free_in_new.end(),
                                          _binded.begin(), _binded.end(),
                                          std::back_inserter(intersection));
                    assert(intersection.size() > 0);

                    std::cerr << "variable_grammar `" << intersection[0] << "` is not free for substitution" << std::endl;
                    exit(1);
                }
            }
        }
    }

    size_t _cnt_intersected = 0; // count of binded variables which exist in _free_in_new
    vertex_ptr_t * _cur_par;
    std::string _var;
    vertex_ptr_t   _new_expr;
    std::set<std::string> _free_in_new; // set of free variables in new expression_grammar, which will be substituted instead of _var
    std::multiset<std::string> _binded;
};
