//
// Created by eugene on 1/31/17.
//
#ifdef _GTEST

#include <gtest/gtest.h>

#include "equation/parser.h"
#include "hw6.h"

TEST(hw6, lambda_function_var) {
    std::string expr = R"(\x. \f. f x)";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "result_type: (t2->((t2->t3)->t3))\n");
}

TEST(hw6, simple_lambda) {
    std::string expr = R"(\x. \f. f (f x))";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "result_type: (t5->((t5->t5)->t5))\n");
}

TEST(hw6, with_free_var) {
    std::string expr = R"(\x. \f . \g. g (i f) (f x))";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "i:: ((t7->t8)->t4)\n"
                   "result_type: (t7->((t7->t8)->((t4->(t8->t9))->t9)))\n");
}

TEST(hw6, difficult_lambda) {
    std::string expr = R"((\f.\x.f (f x)) (\f.\x.f (f x)) (\f.\x.f (f x)) (\f.\x.f (f x)) (\f.\x.f (f x)))";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "result_type: ((t28->t28)->(t28->t28))\n");
}

TEST(hw6, bad_test) {
    std::string expr = R"((\x.x) (\f.\x.x))";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "result_type: (t3->(t2->t2))\n");

}

TEST(hw6, bad_difficult_test) {
    std::string expr = R"((\f.\x.x) (\n.\f.\x.n (\g.\h.h (g f)) (\u.x) (\u.u)) (\f.\x.x))";

    std::string res = hw6::main(expr);

    ASSERT_EQ(res, "result_type: (t17->(t16->t16))\n");
}

TEST(hw6DeathTest, y_combinator) {
    std::string expr = R"(\f.(\x.f (x x)) (\x.f (x x)))";

    ASSERT_DEATH(hw6::main(expr), "");
}

#endif // _GTEST
