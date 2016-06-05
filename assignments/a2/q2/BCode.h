#ifndef BCODE_H
#define BCODE_H

class BCode {
public:
    explicit BCode(const string);   /* Building code */
    string code() const;            /* Accessor -- string code */
    friend ostream& operator<<(ostream&, const BCode&);
    friend bool operator==(const BCode&, const string&);
    friend bool operator==(const BCode&, const BCode&);
    friend bool operator!=(const BCode&, const BCode&);
    friend bool operator<(const BCode&, const BCode&);
    friend bool operator>(const BCode&, const BCode&);

private:
    string _code;
};

#endif
