#include <iostream>
#include <string>
#include "BCode.h"

using namespace std;

BCode::BCodeException::BCodeException(string code)
        : code_(code) {}

string BCode::BCodeException::code() const {
    return code_;
}

BCode::InvalidFormatException::InvalidFormatException(string code, string message)
        : BCodeException(code), message_(message) {}

string BCode::InvalidFormatException::message() const {
    return message_;
}

void BCode::InvalidFormatException::printError() const {
    cout << endl << "ERROR: Building Code \"" << code() << "\" has an invalid format." << endl;
    cout << message();
}

/**
 * Converts a string into a building code after checking for requiremets
 */
BCode::BCode(const string code) {
    string message;

    // length should be b/w 1-3 chars
    if (code.length() < 1 || code.length() > 3) {
        message += "\t- must have length of 2-3 characters\n";

    }
    // first char should be a letter
    if (!isupper(code[0])) {
        message += "\t- must start with a capital letter\n";
    }
    // all chars should be uppercase letters / numbers
    for (int i = 1; i < code.length(); ++i) {
        if (!isdigit(code[i]) && !isupper(code[i])) {
            message += "\t- must consist of only capital letters and digits\n";
            break;
        }
    }

    if (!message.empty()) {
        throw InvalidFormatException(code, message);
    }

    code_ = code;
}

/**
 * @return string Building Code
 */
string BCode::code() const {
    return code_;
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
