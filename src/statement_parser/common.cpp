#include "common.h"

void generate_wrong_arguments_error_message(char *dest, char *args) {
    sprintf(dest, "Wrong arguments: \"%.512s\"", args);
}

void generate_unknown_command_error_message(char *dest, char *command) {
    sprintf(dest, "Unknown command: \"%.512s\"", command);
}