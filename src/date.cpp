#include <iostream>
#include "date.h"
#include "helpers.h"

#define ERROR_MESSAGE_CAP_LEN 32

ParseDateResult *new_parse_date_result() {
    return new ParseDateResult;
}

void delete_parse_date_result(ParseDateResult *parse_date_result) {
    delete parse_date_result->error_message;
    delete parse_date_result;
}

ParseDateResult *parse_date(const char *str, Date *date) {
    auto result = new_parse_date_result();
    size_t len = strlen(str);
    if (str[2] != '.' || str[5] != '.' || len != 10) {
        result->type = PARSE_DATE_WRONG_FORMAT;
        result->error_message = new char[ERROR_MESSAGE_CAP_LEN + len + 1];
        sprintf(result->error_message, "Wrong date format: \"%s\"", str);
        return result;
    }

    char buffer[5]; // used for copying date parts

    // validating day
    strncpy(buffer, str, 2);
    if (!isdigit(buffer[0]) || !isdigit(buffer[1])) {
        result->type = PARSE_DATE_WRONG_DAY_FORMAT;
        result->error_message = new char[ERROR_MESSAGE_CAP_LEN + 2 + 1];
        sprintf(result->error_message, "Day value is invalid: %s", buffer);
        return result;
    }
    date->day = std::stoi(buffer);

    // validating month
    strncpy(buffer, str + 3, 2);
    if (!isdigit(buffer[0]) || !isdigit(buffer[1])) {
        result->type = PARSE_DATE_WRONG_MONTH_FORMAT;
        result->error_message = new char[ERROR_MESSAGE_CAP_LEN + 2 + 1];
        sprintf(result->error_message, "Month value is invalid: %s", buffer);
        return result;
    }
    date->month = std::stoi(buffer);

    //validating year
    strncpy(buffer, str + 3, 2);
    if (!isdigit(buffer[0]) || !isdigit(buffer[1]) || !isdigit(buffer[2]) || !isdigit(buffer[3])) {
        result->type = PARSE_DATE_WRONG_YEAR_FORMAT;
        result->error_message = new char[ERROR_MESSAGE_CAP_LEN + 4 + 1];
        sprintf(result->error_message, "Year value is invalid: %s", buffer);
        return result;
    }
    date->year = std::stoi(buffer);

    return result;
}