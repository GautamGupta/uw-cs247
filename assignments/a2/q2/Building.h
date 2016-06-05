#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>

class Building {
public:
    explicit Building(const BCode, const string);
    explicit Building(const string, const string);
    BCode code() const;
    string name() const;
    friend ostream& operator<<(ostream&, const Building&);

private:
    BCode _code;
    string _name;
};

#endif
