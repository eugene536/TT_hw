//
// Created by eugene on 1/7/17.
//

#pragma once

#include <string>

#include "vertex.h"

struct variable
    : vertex
{
    variable(std::string name);
    virtual void accept(struct visitor * visitor);

    std::string _name;
};

typedef ptr<variable> variable_ptr_t;


