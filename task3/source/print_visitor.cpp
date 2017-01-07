//
// Created by eugene on 1/6/17.
//

#include "print_visitor.h"

int g_cnt_sp;

inline
void print_with_sp(std::string const & s) {
    for (int i = 0; i < g_cnt_sp; ++i) {
        std::cout << " ";
    }

    std::cout << s << std::endl;
}

inline
void inc_sp() {
    g_cnt_sp += 2;
}

inline
void dec_sp() {
    g_cnt_sp -= 2;
}

struct space {
    space() {
        inc_sp();
    }

    ~space() {
        dec_sp();
    }
};

void print_visitor::visit(vertex * v) {
    static_cast<void>(v);

    std::cout << "just v" << std::endl;
}

void print_visitor::visit(lambda * lam) {
    print_with_sp("lambda: ");

    space s;
    static_cast<void>(s);
    lam->_var->accept(this);
    lam->_r_child->accept(this);
}

void print_visitor::visit(application * app) {
    print_with_sp("application_grammar (");
    {
        space s;
        static_cast<void>(s);
        app->_l_child->accept(this);
    }
    print_with_sp(")");

    if (app->_r_child) {
        print_with_sp("(");
        {
            space s;
            static_cast<void>(s);
            app->_r_child->accept(this);
        }
        print_with_sp(")");
    }
}

void print_visitor::visit(variable * var) {
    print_with_sp("variable_grammar: " + var->_name);
}

