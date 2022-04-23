#include "Date.h"

void SimpleDB::Date::julian_date_to_grigorian(unsigned int julian_date, int &day, int &month, int &year) {
    int a = (int) julian_date + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - 146097 * b / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - 1461 * d / 4;
    int m = (5 * e + 2) / 153;
    day = e - (153 * m + 2) / 5 + 1;
    month = m + 3 - 12 * (m / 10);
    year = 100 * b + d - 4800 + m / 10;
}

int SimpleDB::Date::grigorian_to_julian_date(int day, int month, int year) {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + (153 * m + 2) / 5 + 365 * y +
           y / 4 - y / 100 + y / 400 - 32045;
}

std::string SimpleDB::to_string(const SimpleDB::Date &date) { // TODO: use custom string instead of STL's
    int d, m, y;
    Date::julian_date_to_grigorian(date.m_julian_date, d, m, y);
    return std::to_string(d) + std::string(".")
           + std::to_string(m) + std::string(".")
           + std::to_string(y);
}
