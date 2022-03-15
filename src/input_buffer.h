#ifndef ROOM_FOR_SALE_INPUT_BUFFER_H
#define ROOM_FOR_SALE_INPUT_BUFFER_H

#include <iostream>

struct InputBuffer {
    char* buffer;
    size_t buffer_length;
    size_t input_length;
};

InputBuffer* new_input_buffer();

void read_input(InputBuffer* input_buffer);

void delete_input_buffer(InputBuffer* input_buffer);

#endif //ROOM_FOR_SALE_INPUT_BUFFER_H
