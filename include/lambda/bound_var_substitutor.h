//
// Created by eugene on 1/22/17.
//

#pragma once

#include <iostream>
#include <set>
#include <string>

#include "lambda/visitor.h"

struct bound_var_substitutor
        : visitor
{
    bound_var_substitutor(std::string const & var, std::string const & new_var)
        : _old_var(var)
        , _new_var(new_var)
    {}

    virtual void visit(application * app) override {
        app->_l_child->accept(this);
        app->_r_child->accept(this);
    }

    virtual void visit(lambda * lam) override {
        auto it = _bound_vars.insert(lam->_var->_name);

        std::string old_new_var;
        if (lam->_var->_name == _old_var) {
            if (_bound_vars.count(_old_var) > 1) {
                old_new_var = generate_var();
                std::swap(_new_var, old_new_var);
            }

            lam->_var->_name = _new_var;
        }

        lam->_r_child->accept(this);

        if (!old_new_var.empty()) {
            std::swap(_new_var, old_new_var);
        }

        _bound_vars.erase(it);
    }

    virtual void visit(variable * var) override {
        if (_bound_vars.count(var->_name)) {
            if (var->_name == _old_var) {
                var->_name = _new_var;
            }
        }
    }

    std::multiset<std::string> _bound_vars;
    std::string _old_var;
    std::string _new_var;
};

