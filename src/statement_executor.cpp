#include "statement_executor.h"

#include <iostream>

ExecutionResult execute_statement(Statement *statement) {
    switch (statement->type) {
        case STATEMENT_LOAD:
            printf("loaded %s\n", statement->file_name);
            return EXECUTE_SUCCESS;
        case STATEMENT_SAVE:
            printf("saved %s\n", statement->file_name);
            return EXECUTE_SUCCESS;
        case STATEMENT_ADD:
            printf("added row:\n"
                   "date: not implemented\n"
                   "rooms: %d\n"
                   "floor: %d\n"
                   "area: %d\n"
                   "address: %s\n"
                   "price: %d\n",
                   statement->row_to_insert->rooms_amount,
                   statement->row_to_insert->floor,
                   statement->row_to_insert->area,
                   statement->row_to_insert->address,
                   statement->row_to_insert->price
            );
            return EXECUTE_SUCCESS;
        case STATEMENT_DEL:
            printf("deleted row\n");
            return EXECUTE_SUCCESS;
        case STATEMENT_PRINT:
            printf("printed all rows\n");
            return EXECUTE_SUCCESS;
        case STATEMENT_EXPORT:
            printf("exported db\n");
            return EXECUTE_SUCCESS;
        case STATEMENT_FIND:
            printf("found by ID %lld\n", statement->id);
            return EXECUTE_SUCCESS;
        case STATEMENT_EXIT:
            printf("exiting...'n");
            return EXECUTE_EXIT_SUCCESS;
    }
}