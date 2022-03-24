#include <iostream>

#include "statement_parser.h"
#include "common.h"
#include "parse_load.h"
#include "parse_save.h"
#include "parse_add.h"
#include "parse_del.h"
#include "parse_print.h"
#include "parse_find.h"
#include "parse_export.h"


ParseStatementResult *new_parse_statement_result() {
    auto res = new ParseStatementResult;
    res->error_message = new char[1024];
    return res;
}

void delete_parse_statement_result(ParseStatementResult *parse_statement_result) {
    delete[] parse_statement_result->error_message;
    delete parse_statement_result;
}

Statement *new_statement() {
    auto statement = new Statement;
    statement->file_name = new char[64];
    statement->row_to_insert = new_row();
    return statement;
}

void delete_statement(Statement *statement) {
    delete[] statement->file_name;
    delete_row(statement->row_to_insert);
    delete statement;
}

Row *new_row() {
    auto row = new Row;
    row->address = new char[64];
    return row;
}

void delete_row(Row *row) {
    delete[] row->address;
    delete row;
}

ParseStatementResult *parse_statement(InputBuffer *input_buffer, Statement *statement) {
    auto res = new_parse_statement_result();
    res->type = PARSE_SUCCESS;
    if (strncmp(input_buffer->buffer, "load", 4) == 0) {
        parse_load(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "save", 4) == 0) {
        parse_save(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "add", 3) == 0) {
        parse_add(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "del ", 4) == 0) {
        parse_del(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "print", 5) == 0) {
        parse_print(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "export ", 7) == 0) {
        parse_export(res, input_buffer, statement);
        return res;
    } else if (strncmp(input_buffer->buffer, "find ", 5) == 0) {
        parse_find(res, input_buffer, statement);
        return res;
    } else if (strcmp(input_buffer->buffer, "exit") == 0) {
        statement->type = STATEMENT_EXIT;
        res->type = PARSE_SUCCESS;
        return res;
    } else {
        res->type = PARSE_UNKNOWN_COMMAND;
        generate_unknown_command_error_message(res->error_message, input_buffer->buffer);
        return res;
    }
}
