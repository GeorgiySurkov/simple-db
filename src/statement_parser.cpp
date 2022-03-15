#include "statement_parser.h"

#include <iostream>

#include "helpers.h"

#define check_token(token)                     \
    if (token == nullptr || token[0] != ' ') { \
        return PARSE_WRONG_ARGUMENTS;          \
    }

Statement *new_statement() {
    auto statement = new Statement;
    statement->file_name = new char[64];
    statement->row_to_insert = new_row();
    return statement;
}

void delete_statement(Statement *statement) {
    delete statement->file_name;
    delete_row(statement->row_to_insert);
    delete statement;
}

Row *new_row() {
    auto row = new Row;
    row->address = new char[64];
    return row;
}

void delete_row(Row *row) {
    delete row->address;
    delete row;
}

ParseResult parse_statement(InputBuffer *input_buffer, Statement *statement) {
    if (strncmp(input_buffer->buffer, "load", 4) == 0) {
        statement->type = STATEMENT_LOAD;
        int args_wrote = sscanf(
                input_buffer->buffer,
                "load %64s",
                statement->file_name
        );
        if (args_wrote < 1) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strncmp(input_buffer->buffer, "save", 4) == 0) {
        statement->type = STATEMENT_SAVE;
        int args_wrote = sscanf(
                input_buffer->buffer,
                "save %s",
                statement->file_name
        );
        if (args_wrote < 1) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strncmp(input_buffer->buffer, "add", 3) == 0) {
        statement->type = STATEMENT_ADD;
        // copy input buffer to temporary variable for splitting input to tokens
        char *buffer_copy = new char[input_buffer->buffer_length - 3];
        strcpy(buffer_copy, input_buffer->buffer + 3);
        char *token = strtok(buffer_copy, ",");
        check_token(token)
        ++token;
        if (strlen(token) != 10) {
            return PARSE_WRONG_ARGUMENTS;
        }
        char *date_str = token;
        token = strtok(nullptr, ",");
        check_token(token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->rooms_amount))) {
            return PARSE_WRONG_ARGUMENTS;
        }
        token = strtok(nullptr, ",");
        check_token(token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->floor))) {
            return PARSE_WRONG_ARGUMENTS;
        }
        token = strtok(nullptr, ",");
        check_token(token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->area))) {
            return PARSE_WRONG_ARGUMENTS;
        }
        token = strtok(nullptr, ",");
        check_token(token)
        ++token;
        if (strlen(token) > 64) {
            return PARSE_WRONG_ARGUMENTS;
        }
        strcpy(statement->row_to_insert->address, token);
        token = strtok(nullptr, ",");
        check_token(token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->price))) {
            return PARSE_WRONG_ARGUMENTS;
        }
        delete [] buffer_copy;
    } else if (strncmp(input_buffer->buffer, "del", 3) == 0) {
        statement->type = STATEMENT_DEL;
        int args_read = sscanf(
                input_buffer->buffer,
                "del %lld",
                &(statement->id)
        );
        if (args_read < 1) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strncmp(input_buffer->buffer, "print", 5) == 0) {
        statement->type = STATEMENT_PRINT;
        int args_read = sscanf(
                input_buffer->buffer,
                "print %lld",
                &(statement->amount)
        );
        if (args_read == 0) {
            statement->amount = -1;
        } else if (args_read < 0) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strncmp(input_buffer->buffer, "export", 6) == 0) {
        statement->type = STATEMENT_EXPORT;
        int args_read = sscanf(
                input_buffer->buffer,
                "export %64s",
                statement->file_name
        );
        if (args_read < 1) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strncmp(input_buffer->buffer, "find", 4) == 0) {
        statement->type = STATEMENT_FIND;
        int args_read = sscanf(
                input_buffer->buffer,
                "find %lld",
                &(statement->id)
        );
        if (args_read < 1) {
            return PARSE_WRONG_ARGUMENTS;
        }
    } else if (strcmp(input_buffer->buffer, "exit") == 0) {
        statement->type = STATEMENT_EXIT;
    } else {
        return PARSE_UNKNOWN_COMMAND;
    }
    return PARSE_SUCCESS;
}
