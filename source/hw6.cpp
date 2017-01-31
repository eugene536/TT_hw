//
// Created by eugene on 1/31/17.
//

#include <string>
#include <cassert>
#include <map>
#include <sstream>

#include "hw6.h"
#include "lambda/parser.h"
#include "lambda/application.h"
#include "lambda/lambda.h"

namespace hw6 {
    using equation::equation_system_t;
    using equation::equation_t;

    int g_num = 0;

    struct system_with_type {
        equation::vertex_ptr_t _result_type;
        equation::equation_system_t _system;
        std::map<std::string, equation::vertex_ptr_t> _var2type;
    };

    system_with_type generate_system(vertex_ptr_t ver);

    std::string main(std::string const &expr) {
        std::ostringstream oss;
        g_num = 0;
        vertex_ptr_t lambda_expr = parse(expr);

        system_with_type res = generate_system(lambda_expr);
        equation_system_t solution = equation::solve(res._system);

        for (equation_t& eq: solution) {
            assert(eq.first->is_variable());
            res._result_type->substitute(eq.first->_name, eq.second);

            for (auto& p: res._var2type) {
                p.second->substitute(eq.first->_name, eq.second);
            }
        }

        for (auto& p: res._var2type) {
            oss << p.first << ":: " << p.second->to_suffix_string() << std::endl;
        }

        oss << "result_type: ";
        oss << res._result_type->to_suffix_string() << std::endl;

        return oss.str();
    }

    system_with_type generate_system(vertex_ptr_t ver) {
        system_with_type res;

        if (application_ptr_t app = my_dynamic_cast<application>(ver)) {
            system_with_type lhs = generate_system(app->_l_child);
            system_with_type rhs = generate_system(app->_r_child);

            g_num++;
            std::string new_type = "t" + std::to_string(g_num);
            res._result_type = make_ptr<equation::vertex>(new_type);

            res._system = std::move(lhs._system);
            res._system.insert(res._system.end(), rhs._system.begin(), rhs._system.end());

            auto rhs_new_eq = make_ptr<equation::vertex>("->", rhs._result_type, res._result_type);

            equation_t new_eq = std::make_pair(lhs._result_type, rhs_new_eq);
            res._system.push_back(new_eq);

            res._var2type = std::move(lhs._var2type);

            for (auto const & p: rhs._var2type) {
                auto res_insert = res._var2type.insert(p);
                if (!res_insert.second) {
                    equation::vertex_ptr_t prev = res_insert.first->second;
                    equation_t eq_types = std::make_pair(prev, p.second);
                    res._system.push_back(eq_types);
                }
            }

        } else if (lambda_ptr_t lam = my_dynamic_cast<lambda>(ver)) {
            system_with_type in_lam = generate_system(lam->_r_child);
            assert(in_lam._var2type.count(lam->_var->_name));
            equation::vertex_ptr_t lam_t = in_lam._var2type[lam->_var->_name];

            res._result_type = make_ptr<equation::vertex>("->", lam_t, in_lam._result_type);
            res._var2type = std::move(in_lam._var2type);
            res._system = std::move(in_lam._system);
            res._var2type.erase(lam->_var->_name);

        } else if (variable_ptr_t var = my_dynamic_cast<variable>(ver)) {
            g_num++;
            std::string new_type = "t" + std::to_string(g_num);
            res._result_type = make_ptr<equation::vertex>(new_type);
            res._var2type[var->_name] = res._result_type;

        } else {
            assert(("unreachable state", false));
        }

        return res;
    }

} // namespace hw6
