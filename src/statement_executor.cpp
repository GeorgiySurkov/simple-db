#include "statement_executor.h"

#include <iostream>

ExecutionResult execute_statement(Statement *statement) {
    switch (statement->type) {
        case STATEMENT_LOAD:
            printf("loaded \"%s\"\n", statement->file_name);
            return EXECUTE_SUCCESS;
        case STATEMENT_SAVE:
            printf("saved \"%s\"\n", statement->file_name);
            return EXECUTE_SUCCESS;
        case STATEMENT_ADD:
            printf("added row:\n"
                   "date: day: %u, month: %u, year: %u\n"
                   "rooms: %d\n"
                   "floor: %d\n"
                   "area: %d\n"
                   "address: \"%s\"\n"
                   "price: %d\n",
                   // date
                   (unsigned int) statement->row_to_insert->date->day,
                   (unsigned int) statement->row_to_insert->date->month,
                   statement->row_to_insert->date->year,

                   // rooms
                   statement->row_to_insert->rooms_amount,

                   statement->row_to_insert->floor,

                   statement->row_to_insert->area,

                   statement->row_to_insert->address,

                   statement->row_to_insert->price
            );
            return EXECUTE_SUCCESS;
        case STATEMENT_DEL:
            printf("deleted row with ID %lld\n", statement->id);
            return EXECUTE_SUCCESS;
        case STATEMENT_PRINT:
            if (statement->amount == -1) {
                printf("printed all rows\n");
            } else {
                printf("printed %lld row(s)\n", statement->amount);
            }
            return EXECUTE_SUCCESS;
        case STATEMENT_EXPORT:
            printf("exported db to file \"%s\"\n", statement->file_name);
            return EXECUTE_SUCCESS;
        case STATEMENT_FIND:
            printf("found by ID %lld\n", statement->id);
            return EXECUTE_SUCCESS;
        case STATEMENT_EXIT:
            printf("exiting...'n");
            return EXECUTE_EXIT_SUCCESS;
    }
}