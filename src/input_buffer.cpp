#include <iostream>

#include "input_buffer.h"

InputBuffer* new_input_buffer() {
    auto input_buffer = new InputBuffer;
    input_buffer->buffer = nullptr;
    input_buffer->buffer_length = 0;

    return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(
            &(input_buffer->buffer),
            &(input_buffer->buffer_length),
            stdin
    );

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void delete_input_buffer(InputBuffer* input_buffer) {
    delete[] input_buffer->buffer;
    delete input_buffer;
}