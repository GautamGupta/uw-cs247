#include <iostream>
#include "BCode.h"
#include "Building.h"

using namespace std;

/**
 * Creates a new building
 */
Building::Building(const BCode code, const string name) :
        _code(code), _name(name) {}

/**
 * Creates a new building
 */
Building::Building(const string code, const string name) :
        _code(BCode(code)), _name(name) {}

/**
 * @return BCode Building Code
 */
BCode Building::code() const {
    return _code;
}

/**
 * @return string Official Building Name
 */
string Building::name() const {
    return _name;
}

ostream& operator<<(ostream &sout, const Building &building) {
    sout << building.code() << "\t" << building.name();
    return sout;
}
