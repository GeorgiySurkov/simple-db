//-----------------------------------
// This file contains structs and functions for operation with dates
//-----------------------------------
#pragma once

enum ParseDateResultType {
    PARSE_DATE_SUCCESS,
    PARSE_DATE_WRONG_FORMAT,
    PARSE_DATE_WRONG_DAY_FORMAT,
    PARSE_DATE_WRONG_MONTH_FORMAT,
    PARSE_DATE_WRONG_YEAR_FORMAT,
};

struct ParseDateResult {
    ParseDateResultType type;
    char *error_message;
};

ParseDateResult *new_parse_date_result();

void delete_parse_date_result(ParseDateResult *parse_date_result);

struct Date {
    unsigned int day : 5;
    unsigned int month : 3;
    unsigned int year;
};

ParseDateResult *parse_date(const char *str, Date *date);
