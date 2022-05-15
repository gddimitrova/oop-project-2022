#include "Date.h"
#include <iomanip>

Date::Date():mYear(1), mMonth(1), mDay(1)
{
}

Date::Date(int year, int month, int day)
{
    if (!isValidDate(day, month, year))
        throw std::exception("Invalid date!");
    mDay = day;
    mMonth = month;
    mYear = year;
}

Date::Date(const Date& other):Date(other.getYear(), other.getMonth(), other.getDay())
{
}

bool Date::isValidDate(int day, int month, int year) const
{
    if (year < 1 || year>9999) {
        return false;
    }

    bool validDay = false;
    switch (month)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: validDay = (day>=1 && day<=31); break;
    case 4: case 6: case 9: case 11: validDay = (day >= 1 && day <= 30); break;
    case 2: (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? validDay = (day >= 1 && day <= 29) : validDay = (day >= 1 && day <= 28); break;
    default: throw std::exception("Invalid date");
        break;
    }

    return validDay;
}

std::ostream& operator<<(std::ostream& out, const Date& other)
{
    out << std::setfill('0');
    out << std::setw(4) << other.mYear << "-";
    out << std::setfill('0');
    out << std::setw(2) << other.mMonth << "-";
    out << std::setfill('0');
    out << std::setw(2) << other.mDay;

    return out;
}

std::istream& operator>>(std::istream& in, Date& rhs)
{
    int day, month, year;
    char ch;
    in >> year >> ch >> month >> ch >> day;
    rhs.setDay(day);
    rhs.setMonth(month);
    rhs.setYear(year);

    return in;
}
