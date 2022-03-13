#include "statement_parser.h"
#include <iostream>

ParseResult parse_statement(InputBuffer *input_buffer, Statement *statement) {
    if (strncmp(input_buffer->buffer, "load", 4) == 0) {
        statement->type = STATEMENT_LOAD;
        int args_wrote = sscanf(
                input_buffer->buffer,
                "load %s",
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
        char date_str[10];
        int args_wrote = sscanf(
                input_buffer->buffer,
                "add %10s %d %d %d %64s %d",
                date_str,
                &(statement->row_to_insert->rooms_amount),
                &(statement->row_to_insert->floor),
                &(statement->row_to_insert->area),
                statement->row_to_insert->address,
                &(statement->row_to_insert->price)
                );
        if (args_wrote < 6) {
            return PARSE_WRONG_ARGUMENTS;
        }
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
    } else if (strncmp(input_buffer->buffer, "exit", 4) == 0) {
        statement->type = STATEMENT_EXIT;
    } else {
        return PARSE_UNKNOWN_COMMAND;
    }
    return PARSE_SUCCESS;
}
