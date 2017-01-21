//
// Created by eugene on 1/7/17.
//

#pragma once

#include <iostream>

#include "visitor.h"

struct to_string_visitor
    : visitor
{
    to_string_visitor(std::ostream &out)
            : _out(out)
    {}

    void visit(lambda * lam) override {
        _out << "\\";
        lam->_var->accept(this);
        _out << " . (";
        lam->_r_child->accept(this);
        _out << ")";
    }

    void visit(application * app) override {
        _out << "( ";
        app->_l_child->accept(this);
        _out << " ) ";

        _out << "( ";
        app->_r_child->accept(this);
        _out << " )";
    }

    void visit(variable * var) override {
        _out << var->_name;
    }

    std::ostream& _out;
};

inline
std::ostream& operator<<(std::ostream& out, vertex& expr) {
    to_string_visitor string_visitor(out);
    expr.accept(&string_visitor);

    return out;
}

inline
std::string to_string_ver(vertex& expr) {
    std::stringstream ss;
    to_string_visitor string_visitor(ss);
    expr.accept(&string_visitor);

    return ss.str();
}