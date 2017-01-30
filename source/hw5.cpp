//
// Created by eugene on 1/30/17.
//

#include <sstream>
#include <vector>

#include "equation/parser.h"
#include "hw5.h"

namespace hw5 {
    using namespace equation;

    std::string main(std::string const & file) {
        std::istringstream iss(file);
        equation_system_t equation_system;

        std::string eq;
        while (std::getline(iss, eq)) {
            equation_system.push_back(parse(eq));
        }

        equation_system_t solution = solve(equation_system);

        std::ostringstream oss;
        for (equation_t & e: solution) {
            oss << *e.first << " = " << *e.second << std::endl;
        }

        return oss.str();
    }
} // namespace hw5
