#include "parse_add.h"
#include "common.h"
#include "../helpers.h"

#define check_token(res, token)                                                 \
    if ((token) == nullptr || (token)[0] != ' ') {                              \
        (res)->type = PARSE_WRONG_ARGUMENTS;                                    \
        generate_wrong_arguments_error_message((res)->error_message, (token));  \
        return;                                                                 \
    }


void parse_add(ParseStatementResult *res, InputBuffer *input_buffer, Statement *statement) {
    statement->type = STATEMENT_ADD;
    char *args = input_buffer->buffer + 3;
    if (args[0] != ' ') {
        generate_wrong_arguments_error_message(res->error_message, args);
        return;
    }
    ++args;

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
            return;
    }
    delete_parse_date_result(parse_date_res);

    // rooms_amount
    token = strtok(nullptr, ",");
    check_token(res, token)
    ++token;
    if (!strtoint(token, &(statement->row_to_insert->rooms_amount))) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, token);
        return;
    }

    // floor
    token = strtok(nullptr, ",");
    check_token(res, token)
    ++token;
    if (!strtoint(token, &(statement->row_to_insert->floor))) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, token);
        return;
    }

    // area
    token = strtok(nullptr, ",");
    check_token(res, token)
    ++token;
    if (!strtoint(token, &(statement->row_to_insert->area))) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, token);
        return;
    }

    // address
    token = strtok(nullptr, ",");
    check_token(res, token)
    ++token;
    if (strlen(token) > 64) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, token);
        return;
    }
    strcpy(statement->row_to_insert->address, token);

    // price
    token = strtok(nullptr, ",");
    check_token(res, token)
    ++token;
    if (!strtoint(token, &(statement->row_to_insert->price))) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, token);
        return;
    }

    delete[] buffer_copy;
    res->type = PARSE_SUCCESS;
}
