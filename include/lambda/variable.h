//
// Created by eugene on 1/7/17.
//

#pragma once

#include <string>

#include "lambda/vertex.h"

struct variable
    : vertex
{
    variable(std::string name);
    virtual void accept(struct visitor * visitor);
    variable * deep_copy() const override;

    std::string _name;
};

typedef ptr<variable> variable_ptr_t;


