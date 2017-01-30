//
// Created by eugene on 1/30/17.
//

#include <cassert>
#include <string>

#include "equation/parser.h"
#include "lambda/parser.h"

namespace equation {
    namespace details {
        using lambda_parser::skip;
        using lambda_parser::skip_spaces;

        bool is_function(char c) {
            return 'a' <= c && c <= 'h';
        }

        bool is_variable(char c) {
            return 'i' <= c && c <= 'z';
        }

        bool is_symbol(char c) {
            return isalpha(c) || isdigit(c) || c == '\'';
        }

        vertex_ptr_t function(char const *& f, char const * l);
        vertex_ptr_t variable(char const *& f, char const * l);

        vertex_ptr_t term(char const *& f, char const * l) {
            vertex_ptr_t res;
            assert(f < l);

            skip_spaces(f);

            if (is_function(*f)) {
                vertex_ptr_t fun = function(f, l);
                skip('(', f);
                while (f < l) {
                    skip_spaces(f);

                    if (is_symbol(*f)) {
                        vertex_ptr_t child_term = term(f, l);
                        fun->_children.push_back(child_term);
                    } else if (',' == *f) {
                        skip(',', f);
                    } else {
                        break;
                    }
                }
                skip(')', f);

                res = fun;
            } else {
                if (!is_variable(*f)) {
                    std::cerr << "expected variable, but given: " << *f << std::endl;
                    exit(EXIT_FAILURE);
                }

                res = variable(f, l);
            }

            return res;
        }

        vertex_ptr_t function(char const *& f, char const * l) {
            assert(f < l);
            char const * f_old = f;

            while (is_symbol(*f)) {
                ++f;
            }

            return make_ptr<vertex>(std::string(f_old, f));
        }

        vertex_ptr_t variable(char const *& f, char const * l) {
            return function(f, l);
        }
    } // namespace details

    std::pair<vertex_ptr_t, vertex_ptr_t> parse(std::string const & expr) {
        using details::term;

        size_t eq_pos  = expr.find('=');

        if (std::string::npos != eq_pos) {
            char const * left_f = expr.data();
            char const * left_l = left_f + eq_pos - 1;

            char const * right_f = left_l + 2;
            char const * right_l = expr.data() + expr.size();

            return {term(left_f, left_l), term(right_f, right_l)};
        } else {
            std::cerr << "equation::parse - can't find `=` sign" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

} // namespace equation
