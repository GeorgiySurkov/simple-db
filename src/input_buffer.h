#ifndef ROOM_FOR_SALE_INPUT_BUFFER_H
#define ROOM_FOR_SALE_INPUT_BUFFER_H

struct InputBuffer {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

InputBuffer* new_input_buffer();

void read_input(InputBuffer* input_buffer);

void close_input_buffer(InputBuffer* input_buffer);

#endif //ROOM_FOR_SALE_INPUT_BUFFER_H
