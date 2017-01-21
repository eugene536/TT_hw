//
// Created by eugene on 1/6/17.
//

#pragma once

#include <iostream>

#include "visitor.h"

struct print_visitor
    : visitor
{
    print_visitor(std::ostream& out = std::cerr)
        : _out(out)
    {}

    virtual void visit(vertex * v) override;
    virtual void visit(lambda * lam) override;
    virtual void visit(application * app) override;
    virtual void visit(variable * var) override;

private:
    void print_with_sp(std::string const & s);

    std::ostream & _out;
};
