//
// Created by eugene on 1/6/17.
//

#pragma once

#include "visitor.h"

struct print_visitor
    : visitor
{
    virtual void visit(vertex * v) override;
    virtual void visit(lambda * lam) override;
    virtual void visit(application * app) override;
    virtual void visit(variable * var) override;
};
