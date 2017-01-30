//
// Created by eugene on 1/30/17.
//
#ifdef _GTEST

#include <gtest/gtest.h>

#include "equation/parser.h"

struct equation_parser_f
    : ::testing::Test
{
    void test() {
        std::tie(_lhs, _rhs) = equation::parse(lhs + " = " + rhs);

        ASSERT_EQ(_lhs->to_string(), lhs);
        ASSERT_EQ(_rhs->to_string(), rhs);
    }

    std::string lhs;
    std::string rhs;

private:
    equation::vertex_ptr_t _lhs;
    equation::vertex_ptr_t _rhs;
};

TEST_F(equation_parser_f, just_variables) {
    lhs = "x";
    rhs = "y";
    test();
}

TEST_F(equation_parser_f, single_argument_functions) {
    lhs = "f(z)";
    rhs = "h(y)";
    test();
}

TEST_F(equation_parser_f, complex_functions) {
    lhs = "f(g(x, y, a(x, y, z)), z)";
    rhs = "h(y, b(j, k, i, i))";
    test();
}

#endif // _GTEST

