//
// Created by eugene on 1/30/17.
//
#ifdef _GTEST

#include <gtest/gtest.h>

#include "equation/parser.h"
#include "hw5.h"

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

TEST(hw5, trivial_just_vars) {
    std::string const eq = "x = y";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "x = y\n");
}

TEST(hw5, trivial_with_function) {
    std::string const eq = "f(y, g(z))  =  x  ";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "x = f(y, g(z))\n");
}

TEST(hw5, simple_equation) {
    std::string const eq = "f(y, g(z))  =  f(x, y)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "y = g(z)\n"
                   "x = g(z)\n");
}

TEST(hw5, more_dificult_equation) {
    std::string const eq = "f(x, g(y)) = f(e(g(f(t, z))), t)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "t = g(y)\n"
                   "x = e(g(f(g(y), z)))\n");
}

TEST(hw5, dificult_equation) {
    std::string const eq = "f(f(x,g(y)),f(e(g(f(t,z))),t))=f(m,m)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "m = f(e(g(f(g(y), z))), g(y))\n"
                   "t = g(y)\n"
                   "x = e(g(f(g(y), z)))\n");
}

TEST(hw5, simple_system_equation) {
    std::string const eq = "f(g(z, y), h(x, x)) = u\n"
                           "u = f(v, w)\n"
                           "v = g(t, f(m, m))\n"
                           "w = h(y, y)";

    std::string res = hw5::main(eq);

    ASSERT_EQ(res, "u = f(g(z, f(m, m)), h(f(m, m), f(m, m)))\n"
                   "w = h(f(m, m), f(m, m))\n"
                   "v = g(z, f(m, m))\n"
                   "x = f(m, m)\n"
                   "y = f(m, m)\n"
                   "t = z\n");
}

#endif // _GTEST

