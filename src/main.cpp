#include <iostream>

#include "input_buffer.h"
#include "statement_parser.h"
#include "statement_executor.h"

void print_app_info() {
    printf("Room for sale command prompt (v1.0.0)\n");
}

void print_prompt() {
    printf(">> ");
}

void print_unknown_command_error_message(InputBuffer *command) {
    printf("Unknown command: \"%s\"\n", command->buffer);
}

// TODO: display wrong arguments
void print_wrong_arguments_error_message(InputBuffer *command) {
    printf("Wrong arguments\n");
}

int main(){
    print_app_info();
    auto input_buffer = new_input_buffer();
	while (true) {
        print_prompt();
        read_input(input_buffer);

        auto statement = new_statement();
        switch (parse_statement(input_buffer, statement)) {
            case PARSE_SUCCESS:
                break;
            case PARSE_UNKNOWN_COMMAND:
                print_unknown_command_error_message(input_buffer);
                continue;
            case PARSE_WRONG_ARGUMENTS:
                print_wrong_arguments_error_message(input_buffer);
                continue;
        }
        switch (execute_statement(statement)) {
            case EXECUTE_SUCCESS:
                break;
            case EXECUTE_EXIT_SUCCESS:
                delete_input_buffer(input_buffer);
                delete_statement(statement);
                exit(EXIT_SUCCESS);
        }
    }
}
