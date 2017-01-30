//
// Created by eugene on 1/30/17.
//

#include <sstream>

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
