#include <iostream>
#include <string>
#include "BCode.h"

using namespace std;

/**
 * Converts a string into a building code after checking for requiremets
 */
BCode::BCode(const string code) {
    // length should be b/w 1-3 chars
    if (code.length() < 1 || code.length() > 3) {
        exit(1);
    }
    // all chars should be uppercase letters / numbers
    for (int i = 1; i < code.length(); ++i) {
        if (!isdigit(code[i]) && (!isalpha(code[i]) || !isupper(code[i]))) {
            exit(1);
        }
    }
    // first char should be a letter
    if (!isalpha(code[0])) {
        exit(1);
    }

    _code = code;
}

/**
 * @return string Building Code
 */
string BCode::code() const {
    return _code;
}

ostream& operator<<(ostream &sout, const BCode &code) {
    sout << code.code();
    return sout;
}

bool operator== (const BCode &a, const string &b) {
    return a.code().compare(b) == 0;
}

bool operator== (const BCode &a, const BCode &b) {
    return a == b.code();
}

bool operator!= (const BCode &a, const BCode &b) {
    return !(a == b);
}

bool operator< (const BCode &a, const BCode &b) {
    return a.code().compare(b.code()) < 0;
}

bool operator> (const BCode &a, const BCode &b) {
    return a.code().compare(b.code()) > 0;
}
