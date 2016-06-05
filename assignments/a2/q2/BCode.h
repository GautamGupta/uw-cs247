#ifndef BCODE_H
#define BCODE_H

#include <iostream>
#include <string>

class BCode {
public:
    explicit BCode(const std::string);                            /* Building code */
    std::string code() const;                                     /* Accessor -- string code */
    friend std::ostream& operator<<(std::ostream&, const BCode&);
    friend bool operator==(const BCode&, const std::string&);
    friend bool operator==(const BCode&, const BCode&);
    friend bool operator!=(const BCode&, const BCode&);
    friend bool operator<(const BCode&, const BCode&);
    friend bool operator>(const BCode&, const BCode&);

private:
    std::string _code;
};

#endif
