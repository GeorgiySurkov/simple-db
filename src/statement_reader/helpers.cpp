#include "helpers.h"

#include "WrongDateFormatError.h"

namespace SimpleDB {

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

        // TODO: check that the corresponding months have the correct number of days. For e.g. February 30
        // Check that day, month and year are in right ranges
        if (dmy[0] > 31) {
            throw WrongDateFormatError("Day value is invalid"); // TODO: print invalid value
        }
        if (dmy[1] > 12) {
            throw WrongDateFormatError("Month value is invalid"); // TODO: print invalid value
        }
        if (dmy[2] > 9999) {
            throw WrongDateFormatError("Year value is invalid"); // TODO: print invalid value
        }

        return {dmy[0], dmy[1], dmy[2]};
    }

    string trim(const string &s) {
        auto start = s.cbegin();
        while (start != s.cend() && std::isspace(*start)) {
            ++start;
        }

        auto end = s.cend();

        do {
            --end;
        } while (start != end && std::isspace(*end));

        return {start, ++end};
    }

}