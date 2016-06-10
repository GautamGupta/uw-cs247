#ifndef BCODE_H
#define BCODE_H

#include <iostream>
#include <string>

class BCode {
public:
    class BCodeException {
    public:
        BCodeException(const std::string);
        std::string code() const;
        virtual void printError() const = 0;

    private:
        std::string code_;
    };

    class InvalidFormatException : public BCodeException {
    public:
        InvalidFormatException(const std::string, const std::string);
        std::string message() const;
        virtual void printError() const;

    private:
        std::string message_;
    };

    explicit BCode(const std::string);                            /* Building code */
    std::string code() const;                                     /* Accessor -- string code */
    friend std::ostream& operator<<(std::ostream&, const BCode&);
    friend bool operator==(const BCode&, const std::string&);
    friend bool operator==(const BCode&, const BCode&);
    friend bool operator!=(const BCode&, const BCode&);
    friend bool operator<(const BCode&, const BCode&);
    friend bool operator>(const BCode&, const BCode&);

private:
    std::string code_;
};

#endif
