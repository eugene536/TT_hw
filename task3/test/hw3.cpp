//
// Created by eugene on 1/21/17.
//
#ifdef _GTEST

#include <string>

#include <gtest/gtest.h>

#include "to_string_visitor.h"
#include "hw3.h"

std::string convert(std::string const & in) {
    char const * f = in.data();
    char const * l = f + in.size();

    return to_string_ver(*parse(f, l));
}

TEST(hw3, one_app) {
    std::string in = R"(y a [a := \f . f xi''])";
    std::string out = convert(R"(y \f . f xi'')");

    std::string res = hw3::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw3, unused_var) {
    std::string in = R"(x \x . x x \x . x y [a := x x x \x . x x \x . x y])";
    std::string out = convert(R"(x \x . x x \x . x y)");

    std::string res = hw3::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw3, id_subst) {
    std::string in = R"(( \xzxcv . (( ( jlk''' ) ( xzxv ) ) ( ( \b . (( ( a ( b c ) ) ( d ) ) ( ( \e . (( \u . (( \g . (( ( u ) ( f ) ) ( g ))))))) ))) ))) [a := a])";
    std::string out = convert(R"(( \xzxcv . (( ( jlk''' ) ( xzxv ) ) ( ( \b . (( ( a ( b c ) ) ( d ) ) ( ( \e . (( \u . (( \g . (( ( u ) ( f ) ) ( g ))))))) ))) ))))");

    std::string res = hw3::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw3, var_to_const_fun) {
    std::string in = R"(\a . b a [b := \x . x y])";
    std::string out = convert(R"(\a . (\x . x y) a)");

    std::string res = hw3::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw3, rename_var) {
    std::string in = R"(x [ x := y ] )";
    std::string out = convert(R"(y)");

    std::string res = hw3::main(in);
    ASSERT_EQ(res, out);
}

#endif // _GTEST

