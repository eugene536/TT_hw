//
// Created by eugene on 1/7/17.
//

#pragma once
#include <set>
#include <string>

#include "visitor.h"

struct free_visitor
    : visitor
{
    free_visitor(std::set<std::string> & res)
            : _res(res)
    {}

    void visit(lambda * lam) override {
        auto it = _binded.insert(lam->_var->_name);
        lam->_r_child->accept(this);
        _binded.erase(it);
    }

    void visit(variable * var) override {
        if (0 == _binded.count(var->_name)) {
            _res.insert(var->_name);
        }
    }

    std::set<std::string> & _res;
    std::multiset<std::string> _binded;
};



