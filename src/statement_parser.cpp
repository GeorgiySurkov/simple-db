#include <iostream>

#include "statement_parser.h"
#include "helpers.h"
#include "date.h"

#define check_token(res, token)                                                 \
    if ((token) == nullptr || (token)[0] != ' ') {                              \
        res->type = PARSE_WRONG_ARGUMENTS;                                      \
        generate_wrong_arguments_error_message((res)->error_message, (token));  \
        return (res);                                                           \
    }

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

void generate_wrong_arguments_error_message(char *dest, char *args) {
    sprintf(dest, "Wrong arguments: \"%.512s\"", args);
}

void generate_unknown_command_error_message(char *dest, char *command) {
    sprintf(dest, "Unknown command: \"%.512s\"", command);
}

ParseStatementResult *parse_statement(InputBuffer *input_buffer, Statement *statement) {
    auto res = new_parse_statement_result();
    res->type = PARSE_SUCCESS;
    if (strncmp(input_buffer->buffer, "load", 4) == 0) {
        char *args = input_buffer->buffer + 4;
        if (args[0] != ' ') {
            generate_wrong_arguments_error_message(res->error_message, args);
            return res;
        }
        ++args;
        statement->type = STATEMENT_LOAD;
        int args_wrote = sscanf(
                args,
                "%64s",
                statement->file_name
        );
        if (args_wrote < 1) {
            generate_wrong_arguments_error_message(res->error_message, args);
            return res;
        }
    } else if (strncmp(input_buffer->buffer, "save", 4) == 0) {
        char *args = input_buffer->buffer + 4;
        if (args[0] != ' ') {
            generate_wrong_arguments_error_message(res->error_message, args);
            return res;
        }
        ++args;
        statement->type = STATEMENT_SAVE;
        int args_wrote = sscanf(
                args,
                "%64s",
                statement->file_name
        );
        if (args_wrote < 1) {
            generate_wrong_arguments_error_message(res->error_message, args);
            return res;
        }
    } else if (strncmp(input_buffer->buffer, "add", 3) == 0) {
        char *args = input_buffer->buffer + 3;
        if (args[0] != ' ') {
            generate_wrong_arguments_error_message(res->error_message, args);
            return res;
        }
        ++args;
        statement->type = STATEMENT_ADD;

        // copy input buffer to temporary variable for splitting input to tokens
        char *buffer_copy = new char[input_buffer->buffer_length - 3];
        strcpy(buffer_copy, input_buffer->buffer + 3);

        // date
        char *token = strtok(buffer_copy, ",");
        check_token(res, token)
        ++token;
        statement->row_to_insert->date = new Date;
        auto parse_date_res = parse_date(token, statement->row_to_insert->date);
        switch (parse_date_res->type) {
            case PARSE_DATE_SUCCESS:
                break;
            default:
                res->type = PARSE_WRONG_ARGUMENTS;
                strcpy(res->error_message, parse_date_res->error_message);
                delete_parse_date_result(parse_date_res);
                return res;
        }
        delete_parse_date_result(parse_date_res);

        // rooms_amount
        token = strtok(nullptr, ",");
        check_token(res, token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->rooms_amount))) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, token);
            return res;
        }

        // floor
        token = strtok(nullptr, ",");
        check_token(res, token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->floor))) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, token);
            return res;
        }

        // area
        token = strtok(nullptr, ",");
        check_token(res, token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->area))) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, token);
            return res;
        }

        // address
        token = strtok(nullptr, ",");
        check_token(res, token)
        ++token;
        if (strlen(token) > 64) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, token);
            return res;
        }
        strcpy(statement->row_to_insert->address, token);

        // price
        token = strtok(nullptr, ",");
        check_token(res, token)
        ++token;
        if (!strtoint(token, &(statement->row_to_insert->price))) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, token);
            return res;
        }
        delete [] buffer_copy;
    } else if (strncmp(input_buffer->buffer, "del ", 4) == 0) {
        statement->type = STATEMENT_DEL;
        int args_read = sscanf(
                input_buffer->buffer,
                "del %lld",
                &(statement->id)
        );
        if (args_read < 1) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 4);
            return res;
        }
    } else if (strncmp(input_buffer->buffer, "print", 5) == 0) {
        statement->type = STATEMENT_PRINT;
        int args_read = sscanf(
                input_buffer->buffer,
                "print %lld",
                &(statement->amount)
        );
        if (args_read == -1) {
            statement->amount = -1;
        } else if (args_read < 1) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 5);
            return res;
        }
    } else if (strncmp(input_buffer->buffer, "export ", 7) == 0) {
        statement->type = STATEMENT_EXPORT;
        int args_read = sscanf(
                input_buffer->buffer,
                "export %64s",
                statement->file_name
        );
        if (args_read < 1) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 7);
            return res;
        }
    } else if (strncmp(input_buffer->buffer, "find ", 5) == 0) {
        statement->type = STATEMENT_FIND;
        int args_read = sscanf(
                input_buffer->buffer,
                "find %lld",
                &(statement->id)
        );
        if (args_read < 1) {
            res->type = PARSE_WRONG_ARGUMENTS;
            generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 5);
            return res;
        }
    } else if (strcmp(input_buffer->buffer, "exit") == 0) {
        statement->type = STATEMENT_EXIT;
    } else {
        res->type = PARSE_UNKNOWN_COMMAND;
        generate_unknown_command_error_message(res->error_message, input_buffer->buffer);
        return res;
    }
    res->type = PARSE_SUCCESS;
    return res;
}
