#include "parse_del.h"
#include "common.h"

void parse_del(ParseStatementResult *res, InputBuffer *input_buffer, Statement *statement) {
    statement->type = STATEMENT_DEL;
    int args_read = sscanf(
            input_buffer->buffer,
            "del %lld",
            &(statement->id)
    );
    if (args_read < 1) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 4);
        return;
    }
    res->type = PARSE_SUCCESS;
}
