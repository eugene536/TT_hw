//
// Created by eugene on 1/6/17.
//

#include <bits/stdc++.h>

#include "lambda/parser.h"
#include "lambda/application.h"
#include "lambda/lambda.h"

namespace lambda_parser {
    using std::set;
    using std::string;

    bool is_var(char c) {
        return islower(c) || isdigit(c) || c == '\'';
    }

    bool isatom(char c) {
        return c == '(' || islower(c);
    }

    void skip_spaces(char const *&s) {
        for (; isspace(*s); ++s);
    }

    void skip(char c, char const *& f) {
        skip_spaces(f);

        if (c != *f) {
            std::cerr << "not matched: c = " << c << "; f = " << f << std::endl;
            exit(EXIT_FAILURE);
        }
        f++;

        skip_spaces(f);
    }

    void skip(std::string const & str, char const *& f) {
        skip_spaces(f);

        std::string str2(f, f + str.size());
        assert(str == str2);
        f += str.size();

        skip_spaces(f);
    }

    variable_ptr_t variable_grammar(const char *&s) {
        skip_spaces(s);

        assert(islower(*s));

        const char * prev_s = s;
        while (is_var(*s)) {
            ++s;
        }

        variable_ptr_t res = make_ptr<variable>(std::string(prev_s, s));
        skip_spaces(s);

        return res;
    }

    vertex_ptr_t atom_grammar(char const *&s) {
        skip_spaces(s);

        vertex_ptr_t res;

        if (*s == '(') {
            skip('(', s);

            res = expression_grammar(s);

            skip(')', s);
        } else {
            res = variable_grammar(s);
        }

        skip_spaces(s);
        return res;
    }

    vertex_ptr_t application_grammar(const char *&s) {
        skip_spaces(s);

        vertex_ptr_t left_atom = atom_grammar(s);
        while (isatom(*s)) {
            vertex_ptr_t right_atom = atom_grammar(s);
            application_ptr_t app = make_ptr<application>(left_atom, right_atom);
//            left_atom->_parent = app;
//            right_atom->_parent = app;

            left_atom = app;
        }

        return left_atom;
    }

    vertex_ptr_t expression_grammar(const char *&s) {
        skip_spaces(s);

        vertex_ptr_t res(nullptr);
        if (isatom(*s)) {
            res = application_grammar(s);
        }

        if ('\\' == *s) {
            skip('\\', s);

            variable_ptr_t var = variable_grammar(s);

            skip('.', s);

            vertex_ptr_t expr = expression_grammar(s);
            lambda_ptr_t lam = make_ptr<lambda>(var, expr);
//            var->_parent = lam;
//            expr->_parent = lam;

            if (res) {
                res = make_ptr<application>(res, lam);
            } else {
                res = lam;
            }
        }

        skip_spaces(s);
        return res;
    }
} // namespace lambda_parser

vertex_ptr_t parse(char const *&f, char const *l) {
    assert(f && l && f < l);
    return lambda_parser::expression_grammar(f);
}

vertex_ptr_t parse(std::string const &expr) {
    char const * f = expr.data();
    char const * l = f + expr.size();

    return parse(f, l);
}

