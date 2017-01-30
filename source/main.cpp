#include <bits/stdc++.h>

#ifdef _GTEST
#  include <gtest/gtest.h>
#endif

#include "lambda/parser.h"
#include "lambda/print_visitor.h"
#include "hw1.h"
#include "hw2.h"
#include "hw3.h"
#include "hw4.h"
#include "hw5.h"

using namespace std;

string const resources   = "resources/";

string in_file(std::string const & task_number) {
#ifdef DEBUG
    static_cast<void>(task_number);
    return resources + "in";
#else
    return resources + "task" + task_number + ".in";
#endif
}

string out_file(std::string const & task_number) {
#ifdef DEBUG
    static_cast<void>(task_number);
    return resources + "out";
#else
    return resources + "task" + task_number + ".out";
#endif
}

void print_expr(std::string const & expr) {
    char const * f = expr.c_str();
    char const * l = f + expr.size();
    vertex_ptr_t v = parse(f, l);
    print_visitor print_visitor;
    v->accept(&print_visitor);
}

typedef std::string hw_main(std::string const &);

hw_main * hw_mains[] = {
        hw1::main,
        hw2::main,
        hw3::main,
        hw4::main,
        hw5::main
};

int main(int argc, char * argv[]) {
#ifdef _GTEST
    std::cout << "Run tests..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    assert(1 < argc);

    std::string const task_number(argv[1]);
    int task_num = std::stoi(task_number) - 1;

    ifstream in(in_file(task_number));
    string expr;
    getline(in, expr);
//    string expr((istreambuf_iterator<char>(in)),
//                 istreambuf_iterator<char>());

    std::cerr << "initial expression: " << std::endl;
    print_expr(expr);
    hw_main * spec_main = hw_mains[task_num];

    ofstream out(out_file(task_number));
    std::string res = spec_main(expr);
    out << res << std::endl;

    return 0;
#endif // _GTEST
}
