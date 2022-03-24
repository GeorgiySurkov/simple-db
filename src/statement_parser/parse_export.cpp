#include "parse_export.h"
#include "common.h"

void parse_export(ParseStatementResult *res, InputBuffer *input_buffer, Statement *statement) {
    statement->type = STATEMENT_EXPORT;
    int args_read = sscanf(
            input_buffer->buffer,
            "export %64s",
            statement->file_name
    );
    if (args_read < 1) {
        res->type = PARSE_WRONG_ARGUMENTS;
        generate_wrong_arguments_error_message(res->error_message, input_buffer->buffer + 7);
        return;
    }
    res->type = PARSE_SUCCESS;
}