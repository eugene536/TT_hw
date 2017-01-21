//
// Created by eugene on 1/6/17.
//

#include "print_visitor.h"

namespace {
    int g_cnt_sp;

    void inc_sp() {
        g_cnt_sp += 2;
    }

    void dec_sp() {
        g_cnt_sp -= 2;
    }

    struct add_space {
        add_space() {
            inc_sp();
        }

        ~add_space() {
            dec_sp();
        }
    };
}

void print_visitor::print_with_sp(std::string const & s) {
    for (int i = 0; i < g_cnt_sp; ++i) {
        _out << " ";
    }

    _out << s << std::endl;
}

void print_visitor::visit(vertex * v) {
    static_cast<void>(v);

    _out << "just v" << std::endl;
}

void print_visitor::visit(lambda * lam) {
    print_with_sp("lambda: ");

    add_space s;
    static_cast<void>(s);
    lam->_var->accept(this);
    lam->_r_child->accept(this);
}

void print_visitor::visit(application * app) {
    print_with_sp("application_grammar (");
    {
        add_space s;
        static_cast<void>(s);
        app->_l_child->accept(this);
    }
    print_with_sp(")");

    if (app->_r_child) {
        print_with_sp("(");
        {
            add_space s;
            static_cast<void>(s);
            app->_r_child->accept(this);
        }
        print_with_sp(")");
    }
}

void print_visitor::visit(variable * var) {
    print_with_sp("variable_grammar: " + var->_name);
}

