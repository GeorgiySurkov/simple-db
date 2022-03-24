#include <iostream>

#include "input_buffer.h"
#include "statement_parser/statement_parser.h"
#include "statement_executor.h"

void print_app_info() {
    printf("Room for sale command prompt (v1.0.0)\n");
}

void print_prompt() {
    printf(">> ");
}

int main(){
    print_app_info();
    auto input_buffer = new_input_buffer();
	while (true) {
        print_prompt();
        read_input(input_buffer);

        auto statement = new_statement();
        auto parse_result = parse_statement(input_buffer, statement);
        switch (parse_result->type) {
            case PARSE_SUCCESS:
                switch (execute_statement(statement)) {
                    case EXECUTE_SUCCESS:
                        break;
                    case EXECUTE_EXIT_SUCCESS:
                        delete_input_buffer(input_buffer);
                        delete_statement(statement);
                        exit(EXIT_SUCCESS);
                }
                break;
            default:
                if (parse_result->error_message) {
                    printf("%s\n", parse_result->error_message);
                } else {
                    printf("Error while parsing");
                }
        }
        delete_parse_statement_result(parse_result);
        delete_statement(statement);
    }
}
