//
// Created by eugene on 1/30/17.
//

#include <cassert>
#include <string>
#include <map>

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

        vertex_ptr_t function(char const *&f, char const *l);

        vertex_ptr_t variable(char const *&f, char const *l);

        vertex_ptr_t term(char const *&f, char const *l) {
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

        vertex_ptr_t function(char const *&f, char const *l) {
            assert(f < l);
            char const *f_old = f;

            while (is_symbol(*f)) {
                ++f;
            }

            return make_ptr<vertex>(std::string(f_old, f));
        }

        vertex_ptr_t variable(char const *&f, char const *l) {
            return function(f, l);
        }
    } // namespace details

    equation_t parse(std::string const &expr) {
        using details::term;

        size_t eq_pos = expr.find('=');

        if (std::string::npos != eq_pos) {
            char const *left_f = expr.data();
            char const *left_l = left_f + eq_pos - 1;

            char const *right_f = left_l + 2;
            char const *right_l = expr.data() + expr.size();

            return {term(left_f, left_l), term(right_f, right_l)};
        } else {
            std::cerr << "equation::parse - can't find `=` sign" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::map<std::string, vertex_ptr_t> g_var2expr;

    bool do_subst(vertex_ptr_t &ver) {
        bool substituted = false;

        for (auto &name_expr: g_var2expr) {
            std::string const &name = name_expr.first;
            vertex_ptr_t const &new_expr = name_expr.second;

            substituted |= ver->substitute(name, new_expr);
        }

        return substituted;
    }

    bool simplify(equation_t &eq, equation_system_t& system) {
        vertex_ptr_t &lhs = eq.first;
        vertex_ptr_t &rhs = eq.second;
        bool simplified = false;

        // reason for lexicographical order: x = y, y = x
        if (rhs->is_variable() && (!lhs->is_variable() || (rhs->_name < lhs->_name))) {
            std::swap(lhs, rhs);
            simplified = true;
        }

        if (lhs->is_variable()) {
            if (!rhs->contains_var(lhs->_name)) {
                if (g_var2expr.count(lhs->_name)) {
                    auto& t = g_var2expr[lhs->_name];
                    if (*t == *rhs) {
                        return false;
                    }
                }
                simplified |= do_subst(rhs);

                if (0 == g_var2expr.count(lhs->_name)) {
                    g_var2expr[lhs->_name] = rhs;
                } else {
                    vertex_ptr_t & new_expr = g_var2expr[lhs->_name];
                    if (rhs != new_expr) {
                        bool flag = true;
                        for (auto& p: system) {
                            if (*(p.first) == *(eq.second) && *(p.second) == *new_expr) {
                                flag = false;
                                break;
                            }
                        }

                        if (flag) {
                            system.push_back(std::make_pair(eq.second, new_expr));
                        }
                        simplified = true;
                    }
                }
            } else if (*lhs != *rhs) {
                std::cerr << "bad equation, right side contains variable from left: " << std::endl;
                std::cerr << "lhs : " << *lhs << std::endl;
                std::cerr << "rhs : " << *rhs << std::endl;

                exit(EXIT_FAILURE);
            }
        } else { // lhs is not variable && rhs is not variable
            simplified |= do_subst(lhs);
            simplified |= do_subst(rhs);
        }

        return simplified;
    }

    equation_system_t solve(equation_system_t const &system) {
        g_var2expr.clear();

        bool progress = true;
        equation_system_t solution;

        solution.reserve(system.size());
        for (equation_t const &eq: system) {
            equation_t eq_copy(eq.first->deep_copy(), eq.second->deep_copy());
            solution.push_back(eq_copy);
        }

        while (progress) {
            progress = false;

            for (size_t i = 0; i < solution.size(); ++i) {
                equation_t &eq = solution[i];
                vertex_ptr_t &lhs = eq.first;
                vertex_ptr_t &rhs = eq.second;
                bool erase_need = false;
                progress |= simplify(eq, solution);

                if (!lhs->is_variable()) {
                    if (!rhs->is_variable()) {
                        if (lhs->_name == rhs->_name) {
                            auto const &l_chs = lhs->_children;
                            auto const &r_chs = rhs->_children;

                            if (l_chs.size() == r_chs.size()) {
                                assert(l_chs.size() > 0);

                                if (l_chs != r_chs) {
                                    for (size_t ch_pos = 0; ch_pos < l_chs.size(); ++ch_pos) {
                                        solution.push_back({l_chs[ch_pos], r_chs[ch_pos]});
                                    }
                                }

                                erase_need = true;
                            } else {
                                std::cerr << "bad equation, count of arguments in functions doesn't match: "
                                          << std::endl;
                                std::cerr << "lhs: " << *lhs << std::endl;
                                std::cerr << "rhs: " << *rhs << std::endl;

                                exit(EXIT_FAILURE);
                            }
                        }
                    } else {
                        std::cerr << "bad equation, function doesn't match: " << std::endl;
                        std::cerr << "lhs: " << *lhs << std::endl;
                        std::cerr << "rhs: " << *rhs << std::endl;

                        exit(EXIT_FAILURE);
                    }
                } else if (rhs->is_variable() && rhs->_name == lhs->_name) {
                    erase_need = true;
                }

                if (erase_need) {
                    std::swap(solution.back(), solution[i]);
                    solution.pop_back();
                    --i;
                    progress = true;
                }
            }
        }

        return solution;
    }

} // namespace equation
