#ifndef ROOM_FOR_SALE_STATEMENT_EXECUTOR_H
#define ROOM_FOR_SALE_STATEMENT_EXECUTOR_H

#include "statement_parser/statement_parser.h"

enum ExecutionResult {
    EXECUTE_SUCCESS,
    EXECUTE_EXIT_SUCCESS,
};

ExecutionResult execute_statement(Statement *statement);

#endif //ROOM_FOR_SALE_STATEMENT_EXECUTOR_H
