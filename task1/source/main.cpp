#include <bits/stdc++.h>
#include <cctype>

using namespace std;

string expression(const char *& s);
string application(const char*& s);
string atom(const char*& s);
string variable(const char*& s);

const string resources = "resources/";
const string in_file   = resources + "task1.in";
const string out_file  = resources + "task1.out";

//expression  = application? '\' variable '.' expression
//            | application
//application = atom (' '* atom)*
//atom        = '(' expression ')' | variable
//variable    = ['a'..'z']['a'..'z','0'..'9','\'']*

inline
void skip_spaces(const char*& s) {
    for (; isspace(*s); ++s);
}

inline
string variable(const char*& s) {
    assert(islower(*s));
    string res(1, *s++);
    for (char c = *s; islower(c) || isdigit(c) || c == '\''; res.push_back(c), c = *++s);
    skip_spaces(s);
    return res;
}

inline
string atom(const char*& s) {
    if (*s == '(') {
        skip_spaces(++s);
        string res = "(" + expression(s) + ")";
        skip_spaces(s);
        assert(*s == ')');
        skip_spaces(++s);
        return res;
    }

    return variable(s);
}

inline
bool isatom(char c) {
    return c == '(' || islower(c);
}

inline
string application(const char*& s) {
    int cnt = 0;
    string res = atom(s);
    while (isatom(*s)) {
        res += " " + atom(s) + ")";
        cnt++;
    }

    string parntss;
    for (; cnt > 0; cnt--, parntss.push_back('('));
    return parntss + res;
}

inline
string expression(const char *& s) {
    string app;
    if (isatom(*s))
        app = application(s);

    if ('\\' == *s) {
        skip_spaces(++s);
        app += "(\\" + variable(s) + ". ";

        assert('.' == *s);
        skip_spaces(++s);
        return "(" + app + expression(s) + "))";
    } else
        return app;
}

const char* ss;
inline string put_parentheses(string expr) {
    const char * s = expr.c_str();
    ss = s;
    skip_spaces(s);
    string res = expression(s);
    assert(s == expr.c_str() + expr.size());
    return res;
}

int main() {
    ifstream in(in_file);
    string expr((istreambuf_iterator<char>(in)),
                 istreambuf_iterator<char>());

    ofstream(out_file) << put_parentheses(expr);
    return 0;
}
