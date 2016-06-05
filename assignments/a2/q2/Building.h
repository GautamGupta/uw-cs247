#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>
#include "BCode.h"

class Building {
public:
    explicit Building(const BCode, const std::string);
    explicit Building(const std::string, const std::string);
    BCode code() const;
    std::string name() const;
    friend std::ostream& operator<<(std::ostream&, const Building&);

private:
    BCode _code;
    std::string _name;
};

#endif
