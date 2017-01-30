//
// Created by eugene on 1/7/17.
//

#include <sstream>

#include "hw1.h"
#include "lambda/to_string_visitor.h"

namespace hw1 {

    std::string main(std::string const &expr) {
        char const * f = expr.c_str();
        char const * l = f + expr.size();

        vertex_ptr_t expr_tree = parse(f, l);

        if (f != l) {
            std::cerr << "hw1:: f != l:: " << std::string(f, l) << std::endl;
        }

        std::stringstream ss;
        to_string_visitor string_visitor(ss);
        expr_tree->accept(&string_visitor);

        return ss.str();
    }

} // namespace hw1

namespace {
    int gen_var = 0;
}

void clear_var_generator() {
    gen_var = 0;
}

std::string generate_var() {
    gen_var++;
    return "a" + std::to_string(gen_var);
}
