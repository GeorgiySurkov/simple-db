#include <iostream>

#include "input_buffer.h"

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

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
