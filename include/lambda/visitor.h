//
// Created by eugene on 1/6/17.
//

#pragma once

#include "lambda/parser.h"
#include "lambda.h"
#include "application.h"
#include "lambda/variable.h"

struct visitor {
    virtual ~visitor() {}

    virtual void visit(vertex * v) {
        static_cast<void>(v);
    }

    virtual void visit(lambda * l) {
        l->_var->accept(this);
        l->_r_child->accept(this);
    }

    virtual void visit(application * app) {
        app->_l_child->accept(this);
        app->_r_child->accept(this);
    }

    virtual void visit(variable * app) = 0;
};

