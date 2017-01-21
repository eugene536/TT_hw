//
// Created by eugene on 1/21/17.
//
#ifdef _GTEST

#include <string>

#include <gtest/gtest.h>

#include "hw4.h"

TEST(hw4, single_var) {

    std::string in = R"(x)";
    std::string out = R"(x)";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, single_betta_red) {

    std::string in = R"((\x . x (\x . x)) y)";
    std::string out = R"(( y ) ( \x . (x) ))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, just_id) {
    std::string in = R"(\x . x)";
    std::string out = R"(\x . (x))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, red_to_id) {
    std::string in = R"((\x.\y.\z.x z (y z)) (\x.\y.x) (\x.x))";
    std::string out = R"(\z . (z))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, second) {
    std::string in = R"((\x . \y . x (\f . \z . f (f z)) ((\x . x x) (\x . x x))) (\x . \y . x) ((\x . x x) (\x . x x)))";
    std::string out = R"(\f . (\z . (( f ) ( ( f ) ( z ) ))))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, test5) {
    std::string in = R"((\y.\m.y (\f.\n.(\s.(s (\x.\a.\b.b) (\a.\b.a)) (\f.\x.x) (f s)) (m n)) (\f.\x.f (f (f x)))) (\f.(\x.f (x x)) (\x.f (x x))) ((\n.\f.\x.n (\g.\h.h (g f)) (\u.x) (\u.u))))";
    std::string out = R"(\f . (\x . (x)))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, test4) {
    std::string in = R"((\n.\f.\x.n (\g.\h.h (g f)) (\u.x) (\u.u)) (\f.\x.f (f (f x))))";
    std::string out = R"(\f . (\x . (( f ) ( ( f ) ( x ) ))))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

TEST(hw4, one_minute) {
    std::string in = R"((\s.\k.\i.(((s ((s (k s)) ((s ((s (k s)) ((s (k k)) i))) (k ((s (k (s ((s (k s)) ((s (k (s (k (s ((s ((s ((s i) (k (k (k i))))) (k ((s (k k)) i)))) (k ((s ((s (k s)) ((s (k k)) i))) (k i))))))))) ((s ((s (k s)) ((s (k k)) ((s (k s)) ((s (k (s (k ((s ((s (k s)) ((s (k k)) ((s (k s)) ((s (k k)) i))))) (k ((s ((s (k s)) ((s (k k)) i))) (k i)))))))) ((s ((s (k s)) ((s (k k)) i))) (k i))))))) (k ((s (k k)) i)))))))) ((s (k k)) ((s ((s (k s)) ((s (k k)) i))) (k i)))))))) (k (k ((s ((s (k s)) ((s (k k)) i))) ((s ((s (k s)) ((s (k k)) i))) ((s ((s (k s)) ((s (k k)) i))) (k i))))))) ((s ((s ((s (k s)) ((s (k k)) i))) (k ((s i) i)))) ((s ((s (k s)) ((s (k k)) i))) (k ((s i) i))))) ((s ((s (k s)) ((s (k (s (k s)))) ((s ((s (k s)) ((s (k (s (k s)))) ((s (k (s (k k)))) ((s ((s (k s)) ((s (k k)) i))) (k ((s (k (s (k (s i))))) ((s (k (s (k k)))) ((s (k (s i))) ((s (k k)) i)))))))))) (k (k ((s (k k)) i))))))) (k (k (k i))))) (\x.\y.\z.x z (y z)) (\x.\y.x) (\x.x))";
    std::string out = R"((\z.(\t1.(z (z (z (z (z (z t1)))))))))";

    std::string res = hw4::main(in);
    ASSERT_EQ(res, out);
}

#endif // _GTEST
