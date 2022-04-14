#ifndef ROOM_FOR_SALE_DATE_H
#define ROOM_FOR_SALE_DATE_H

#include "./string.h"

namespace SimpleDB {
    class Date {
        unsigned int m_julian_date;

        static void julian_date_to_grigorian(unsigned int julian_date, int &day, int &month, int &year);

        static int grigorian_to_julian_date(int day, int month, int year);

    public:
        explicit Date(unsigned int x = 0) : m_julian_date(x) {}

        Date(int day_, int month, int year) : m_julian_date(grigorian_to_julian_date(day_, month, year)) {}

        [[nodiscard]] int day() const {
            int d, m, y;
            julian_date_to_grigorian(m_julian_date, d, m, y);
            return d;
        }

        [[nodiscard]] int month() const {
            int d, m, y;
            julian_date_to_grigorian(m_julian_date, d, m, y);
            return m;
        }

        [[nodiscard]] int year() const {
            int d, m, y;
            julian_date_to_grigorian(m_julian_date, d, m, y);
            return y;
        }

        friend std::string to_string(const Date &date);

        bool operator<(const Date &X) const { return m_julian_date < X.m_julian_date; }

        bool operator==(const Date &X) const { return m_julian_date == X.m_julian_date; }

        bool operator<=(const Date &X) const { return m_julian_date <= X.m_julian_date; }

        bool operator>(const Date &X) const { return X < *this; }

        bool operator>=(const Date &X) const { return X <= *this; }

        Date &operator++() {
            ++m_julian_date;
            return *this;
        }

        Date operator++(int) {
            Date tmp(*this);
            ++m_julian_date;
            return tmp;
        }

        Date &operator--() {
            --m_julian_date;
            return *this;
        }

        Date operator--(int) {
            Date tmp(*this);
            --m_julian_date;
            return tmp;
        }

        Date &operator+=(int x) {
            m_julian_date += x;
            return *this;
        }

        friend Date operator+(Date date, int x) {
            date += x;
            return date;
        }

        int operator-(const Date &x) const {
            return m_julian_date - x.m_julian_date;
        }
    };
}

#endif //ROOM_FOR_SALE_DATE_H
