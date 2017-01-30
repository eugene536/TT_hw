//
// Created by eugene on 1/7/17.
//

#include <sstream>

#include "hw2.h"
#include "lambda/free_visitor.h"

namespace hw2 {

    std::set<std::string> get_free_vars(vertex_ptr_t vertex) {
        std::set<std::string> res;
        free_visitor visitor(res);
        vertex->accept(&visitor);

        return res;
    }

    std::string main(std::string const &expr) {
        char const * f = expr.c_str();
        char const * l = f + expr.size();

        vertex_ptr_t expr_tree = parse(f, l);

        if (f != l) {
            std::cerr << "hw2:: f != l:: " << std::string(f, l) << std::endl;
        }

        std::stringstream ss;
        auto free_vars = get_free_vars(expr_tree);
        for (auto& var: free_vars) {
            ss << var << std::endl;
        }

        return ss.str();
    }

} // namespace hw1
