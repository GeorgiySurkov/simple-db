#include "parse_save.h"
#include "common.h"

void parse_save(ParseStatementResult *res, InputBuffer *input_buffer, Statement *statement) {
    statement->type = STATEMENT_SAVE;
    char *args = input_buffer->buffer + 4;
    if (args[0] != ' ') {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, args);
        return;
    }
    ++args;
    int args_wrote = sscanf(
            args,
            "%64s",
            statement->file_name
    );
    if (args_wrote < 1) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, args);
        return;
    }
    res->type = PARSE_SUCCESS;
}