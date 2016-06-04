#include <iostream>
#include <map>
#include <ctime>
#include "Date.h"

using namespace std;

/**
 * Date Declaration
 */

struct Date::Impl {
    int day;
    string month;
    int year;
};

/**
 * Helper functions
 */

namespace {
    map<string, int> createMonthNumberMap() {
        map<string, int> m;
        m["January"]   =  1;
        m["February"]  =  2;
        m["March"]     =  3;
        m["April"]     =  4;
        m["May"]       =  5;
        m["June"]      =  6;
        m["July"]      =  7;
        m["August"]    =  8;
        m["September"] =  9;
        m["October"]   = 10;
        m["November"]  = 11;
        m["December"]  = 12;

        return m;
    }

    map<string, int> const monthNumber = createMonthNumberMap();
    int const monthNumDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string const monthNames[] = {"", "January", "February", "March", "April", "May",
            "June", "July", "August", "September", "October", "November", "December"};

    /**
     * Get month number from month name. Returns 0 if month isn't found.
     */
    int getMonthNumber(string month) {
        map<string, int>::const_iterator monthSearch = monthNumber.find(month);
        if (monthSearch == monthNumber.end()) {
            return 0;
        }
        return monthSearch->second;
    }

    int getMonthNumDays(int month) {
        return monthNumDays[month];
    }

    string getMonthName(int month) {
        return monthNames[month];
    }

    bool isLeapYear(int year) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            return true;
        }

        return false;
    }

    /**
     * Assumes valid month and year
     *
     * @return int Day of year. Returns 0 if date is invalid
     */
    int dayOfYear(int day, int month, int year) {
        // Prelim tests
        if (day > 31 || day < 1) {
            return 0;
        }

        /* Index, Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec */

        bool isLeap = isLeapYear(year);

        // Check for Feb and leap
        if ((month != 2 || !isLeap) && day > getMonthNumDays(month)) {
            return 0;
        } else if (month == 2 && isLeap && day > (getMonthNumDays(month) + 1)) {
            return 0;
        }

        int day_of_year = 0;

        // Count the days
        for (int i = 1; i < month; i++) {
            day_of_year += getMonthNumDays(i);
        }
        // Add 1 for leap year Feb
        if (month > 2 && isLeap) {
            day_of_year++;
        }

        day_of_year += day;

        return day_of_year;
    }

    /**
     * @return int Day of year. Returns 0 if date is invalid
     */
    int dayOfYear(Date date) {
        return dayOfYear(date.day(), getMonthNumber(date.month()), date.year());
    }

    Date incDate(Date date, int incYears, int incMonths = 0, long incDays = 0) {
        int newDays     = date.day() + incDays;
        string newMonth = getMonthName((getMonthNumber(date.month()) + incMonths) % 12);
        int newYear     = date.year() + incYears + (incMonths / 12);
        return Date(newDays, newMonth, newYear);
    }
} // namespace

Date Date::today() {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    char month_name[10];
    strftime(month_name, sizeof(month_name), "%B", now);

    return Date(now->tm_mday, month_name, now->tm_year + 1900);
}

int Date::checkYear(int year) {
    if (year < 1900 || year > 2100) {
        throw "Invalid year.";
        return 0;
    } else {
        return year;
    }
}

int Date::checkMonth(int month) {
    if (month < 1 || month > 12) {
        throw "Invalid month.";
        return 0;
    } else {
        return month;
    }
}

int Date::checkDay(int day, int month, int year) {
    if (dayOfYear(day, month, year) == 0) {
        throw "Invalid day of the month.";
        return 0;
    } else {
        return day;
    }
}

/**
 * Constructors, destructors, Assignment
 */

Date::Date(int day, string month, int year) :
        date_(new Impl) {
    int monthNumber = checkMonth(getMonthNumber(month));

    date_->year  = checkYear(year);
    date_->month = month;
    date_->day   = checkDay(day, monthNumber, year);
}

Date::~Date() {
    delete date_;
    date_ = NULL;
}

Date::Date(const Date &date) :
        date_(new Impl(*date.date_)) {
}

Date& Date::operator=(const Date &date) {
    Date copy(date);
    Date::Impl* temp;

    temp = copy.date_;
    copy.date_ = date_;
    date_ = temp;

    return *this;
}

/**
 * Accessors
 */

int Date::day() const {
    return date_->day;
}

string Date::month() const {
    return date_->month;
}

int Date::year() const {
    return date_->year;
}

/**
 * Streaming Functions
 */

ostream& operator<<(ostream& sout, const Date &date) {
    sout << date.day() << " " << date.month() << ", " << date.year();
    return sout;
}

istream& operator>>(istream& sin, Date &date) {
    int newDay, newYear;
    string newMonth;
    char comma;

    sin >> newDay >> newMonth >> comma >> newYear;

    date = Date(newDay, newMonth, newYear);

    return sin;
}

/**
 * Comparison Operations
 */

bool operator==(const Date &date1, const Date &date2) {
    return  date1.day()   == date2.day()   &&
            date1.month() == date2.month() &&
            date1.year()  == date2.year();
}

bool operator!=(const Date &date1, const Date &date2) {
    return !(date1 == date2);
}

bool operator>(const Date &date1, const Date &date2) {
    return date1.year() > date2.year() ||
            (date1.year() == date2.year() && dayOfYear(date1) > dayOfYear(date2));
}

bool operator>=(const Date &date1, const Date &date2) {
    return date1 > date2 || date1 == date2;
}

bool operator<(const Date &date1, const Date &date2) {
    return !(date1 >= date2);
}

bool operator<=(const Date &date1, const Date &date2) {
    return !(date1 > date2);
}

/**
 * Increment Functions
 */

Date incYears(const Date &date, int incYears) {
    return incDate(date, incYears, 0, 0);
}

Date incMonths(const Date &date, int incMonths) {
    return incDate(date, 0, incMonths, 0);
}

Date incDays(const Date &date, long incDays) {
    return incDate(date, 0, 0, incDays);
}
