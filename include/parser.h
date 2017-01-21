//
// Created by eugene on 1/6/17.
//

#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "variable.h"

namespace parser {
    void skip_spaces(char const *&s);
    void skip(char c, char const *& f);
    void skip(std::string const & str, char const *& f);

    bool is_var(char c);
    bool isatom(char c);

    vertex_ptr_t expression_grammar(const char *&s);
    vertex_ptr_t application_grammar(const char *&s);
    vertex_ptr_t atom_grammar(char const *&s);
    variable_ptr_t variable_grammar(const char *&s);
}

vertex_ptr_t parse(char const *&f, char const *l);
