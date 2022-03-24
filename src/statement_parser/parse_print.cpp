#include "parse_print.h"
#include "common.h"

void parse_print(ParseStatementResult *res, InputBuffer *input_buffer, Statement *statement) {
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
        return;
    }
    res->type = PARSE_SUCCESS;
}