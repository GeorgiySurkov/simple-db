#include "input_buffer.h"

#ifndef ROOM_FOR_SALE_STATEMENT_PREPROCESSOR_H
#define ROOM_FOR_SALE_STATEMENT_PREPROCESSOR_H

enum ParseResult {
    PARSE_SUCCESS,
    PARSE_UNKNOWN_COMMAND,
    PARSE_WRONG_ARGUMENTS,
    // TODO: add date format errors handling
};

enum StatementType {
    STATEMENT_LOAD,
    STATEMENT_SAVE,
    STATEMENT_ADD,
    STATEMENT_DEL,
    STATEMENT_PRINT,
    STATEMENT_EXPORT,
    STATEMENT_FIND,
    STATEMENT_EXIT,
};

typedef long long ID;

struct Row {
    ID id;
    int rooms_amount;
    int floor;
    int area;
    char * address;
    int price;
};

struct Statement {
    StatementType type;

    // used by STATEMENT_LOAD, STATEMENT_SAVE, STATEMENT_EXPORT
    char *file_name;

    // used by STATEMENT_ADD
    Row *row_to_insert;

    // used by STATEMENT_DEL, STATEMENT_FIND
    ID id;

    // used by STATEMENT_PRINT
    long long amount;
};

ParseResult parse_statement(InputBuffer *input_buffer, Statement *statement);

#endif //ROOM_FOR_SALE_STATEMENT_PREPROCESSOR_H
