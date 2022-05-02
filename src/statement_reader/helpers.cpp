#include "helpers.h"

#include "WrongDateFormatError.h"

namespace SimpleDB {

    const char *months[12] = {
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
    };

    bool is_leap_year(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    Date parse_date(const string &s, char delim) {
        int dmy[3] = {0, 0, 0};
        int tmp, s_index, dmy_index;

        // read day, month and year from a string
        for (s_index = 0, dmy_index = 0; s[s_index] != 0 && dmy_index < 3; ++dmy_index) {
            tmp = 0;
            while ('0' <= s[s_index] && s[s_index] <= '9') {
                tmp = tmp * 10 + (s[s_index] - '0');
                ++s_index;
            }
            dmy[dmy_index] = tmp;
            if (dmy_index < 2) {
                if (s[s_index] != delim) {
                    throw WrongDateFormatError("Wrong date format: " + string(s));
                } else {
                    ++s_index;
                }
            }
        }
        if (s[s_index] != 0) {
            throw WrongDateFormatError("Wrong date format: " + string(s));
        }

        // Check that year, month and day are in right ranges
        if (dmy[2] > 9999) {
            char err[256];
            snprintf(err, 256, "Year value is invalid: %d", dmy[2]);
            throw WrongDateFormatError(err);
        }
        if (dmy[1] > 12) {
            char err[256];
            snprintf(err, 256, "Month value is invalid: %d", dmy[1]);
            throw WrongDateFormatError(err);
        }
        int max_days_in_month;
        switch (dmy[1]) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                max_days_in_month = 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                max_days_in_month = 30;
                break;
            case 2:
                max_days_in_month = is_leap_year(dmy[2]) ? 29 : 28;
                break;
        }
        if (dmy[0] > max_days_in_month) {
            char err[256];
            snprintf(
                    err,
                    256,
                    "Day value is invalid: %d\nThere are %d days in %s",
                    dmy[0],
                    max_days_in_month,
                    months[dmy[1] - 1]
            );
            throw WrongDateFormatError(err);
        }

        return {dmy[0], dmy[1], dmy[2]};
    }

}