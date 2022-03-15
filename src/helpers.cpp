#include "helpers.h"

#include <iostream>

bool strtoint(const char *str, int *number) {
    long a;
    char *endptr;
    errno = 0;
    a = strtol(str, &endptr, 10);
    if (errno == ERANGE) {
        // out of range for a long
        return false;
    }
    if (endptr == str) {
        // no character was read
        return false;
    }
    if (*endptr && *endptr != '\n') {
        // *endptr is neither end of string nor newline,
        // so we didn't convert the *whole* input
        return false;
    }
    if (a > INT_MAX || a < INT_MIN) {
        // result will not fit in an int
        return false;
    }

    // write result through the pointer passed
    *number = (int) a;
    return true;
}
