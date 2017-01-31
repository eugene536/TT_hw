//
// Created by eugene on 1/30/17.
//

#include <sstream>
#include <cassert>

#include "equation/parser.h"

namespace equation {
    vertex::vertex()
    {}

    vertex::vertex(std::string const & name)
        : _name(name)
    {}

    std::string vertex::to_string() const {
        std::stringstream ss;
        ss << *this;

        return ss.str();
    }

    bool vertex::is_variable() const {
        return _children.empty();
    }

    bool vertex::contains_var(std::string const & var) const {
        bool contains = _name == var;

        for (auto const & child: _children) {
            contains = child->contains_var(var);

            if (contains) {
                break;
            }
        }

        return contains;
    }

    bool vertex::substitute(std::string const &var, vertex_ptr_t const & expr) {
        bool substituted = false;

        if (var == _name) {
            _name = expr->_name;

            for (auto const & c: expr->_children) {
                _children.push_back(c->deep_copy());
            }

            substituted = true;
        } else {
            for (vertex_ptr_t &v: _children) {
                if (v->is_variable()) {
                    if (var == v->_name) {
                        v = expr->deep_copy();
                        substituted = true;
                    }
                } else {
                    substituted |= v->substitute(var, expr);
                }
            }
        }

        return substituted;
    }

    vertex_ptr_t vertex::deep_copy() const {
        vertex_ptr_t copy = make_ptr<vertex>(_name);

        if (!is_variable()) {
            for (vertex_ptr_t const & v: _children) {
                copy->_children.push_back(v->deep_copy());
            }
        }

        return copy;
    }

    bool vertex::operator==(vertex const & rhs) const {
        bool res = true;

        if (_name == rhs._name) {
            if (_children.size() == rhs._children.size()) {
                for (size_t i = 0; i < _children.size(); ++i) {
                    if (_children[i] != rhs._children[i]) {
                        res = false;
                        break;
                    }
                }
            } else {
                res = false;
            }
        } else {
            res = false;
        }

        return res;
    }

    bool vertex::operator!=(vertex const & rhs) const {
        return !(*this == rhs);
    }

    std::string vertex::to_suffix_string() const {
        std::string res;
        if (_children.empty()) {
            res = _name;
        } else {
            assert(_children.size() == 2);
            res += "(" + _children.front()->to_suffix_string();
            res += _name;
            res += _children.back()->to_suffix_string() + ")";
        }

        return res;
    }

    std::ostream& operator<<(std::ostream& out, vertex const & ver) {
        if (ver._children.empty()) {
            return out << ver._name;
        }

        out << ver._name << "(";
        for (size_t i = 0; i < ver._children.size() - 1; ++i) {
            out << *(ver._children[i]) << ", ";
        }
        out << *(ver._children.back()) << ")";

        return out;
    }
}
