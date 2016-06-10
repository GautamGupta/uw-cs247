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
    bool isLeapYear(int year) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            return true;
        }

        return false;
    }

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

    /**
     * Get month number from month name. Returns 0 if month isn't found.
     */
    int getMonthNumber(string month) {
        map<string, int> const monthNumber = createMonthNumberMap();
        map<string, int>::const_iterator monthSearch = monthNumber.find(month);
        if (monthSearch == monthNumber.end()) {
            return 0;
        }
        return monthSearch->second;
    }

    /**
     * Assumes valid input
     */
    int getMonthNumDays(int month, int year = 0) {
        int const monthNumDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int numDays = monthNumDays[month];
        if (month == 2 && isLeapYear(year)) {
            numDays++;
        }

        return numDays;
    }

    /**
     * Assumes valid input
     */
    string getMonthName(int month) {
        string const monthNames[] = {"", "January", "February", "March", "April", "May",
                "June", "July", "August", "September", "October", "November", "December"};
        return monthNames[month];
    }

    /**
     * Assumes valid day, month, and year
     *
     * @return int Day of year. Returns 0 if date is invalid
     */
    int dayOfYear(int day, int month, int year) {
        // Count the days
        int day_of_year = day;
        for (int i = 1; i < month; i++) {
            day_of_year += getMonthNumDays(i, year);
        }

        return day_of_year;
    }

    /**
     * @return int Day of year. Returns 0 if date is invalid
     */
    int dayOfYear(Date date) {
        return dayOfYear(date.day(), getMonthNumber(date.month()), date.year());
    }

    Date incDate(const Date &date, int incYears, int incMonths = 0, long incDays = 0) {
        // Let's calculate without days first
        int newYear  = date.year() + incYears;
        int newMonth = getMonthNumber(date.month()) + incMonths;
        while (newMonth > 12) {
            newYear++;
            newMonth -= 12; // Need to implement loop because months start at 1 not 0
        }

        // Round down for month increment
        int monthNumDays = getMonthNumDays(newMonth, newYear);
        if (date.day() > monthNumDays) {
            incDays -= date.day() - monthNumDays;
        }

        // Increment months and years for days
        long newDays = date.day() + incDays;
        while (newDays > monthNumDays) {
            newDays -= monthNumDays;
            newMonth += 1;
            if (newMonth > 12) {
                newYear++;
                newMonth = 1;
            }
            monthNumDays = getMonthNumDays(newMonth, newYear);
        }

        return Date(newDays, getMonthName(newMonth), newYear);
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
    if (day > getMonthNumDays(month, year) || day < 1) {
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

    sin >> newDay >> newMonth >> newYear;
    if (!sin) {
        return sin;
    }

    newMonth = newMonth.substr(0, newMonth.length()-1);
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
