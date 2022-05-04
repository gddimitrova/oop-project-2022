#include "Date.h"
#include <iomanip>

Date::Date():mYear(0001), mMonth(1), mDay(1)
{
}

Date::Date(int year, int month, int day):mDay(day), mMonth(month), mYear(year)
{
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
