
#include "VM.h"

/* libc */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define ELEM_SIZE(arr) sizeof(arr[0])

#define ERR(exit_code) \
    if (bytecode_file) { \
        fclose(bytecode_file); \
    } \
    return exit_code

int main(int argc, char* argv[])
{
    const char* bytecode_filepath = argc == 2? argv[1] : argv[0];
    FILE* bytecode_file = NULL;
    char magic_sig[8];
    uint32_t bytecode_size;
    uint8_t* bytecode = NULL;
    size_t ret;

    bytecode_file = fopen(bytecode_filepath, "r");
    if (!bytecode_file) {
        ERR(41); /* failed to open file */
    }

    fseek(bytecode_file, -sizeof(magic_sig) - sizeof(bytecode_size), SEEK_END);

    ret = fread(magic_sig, ELEM_SIZE(magic_sig), LEN(magic_sig), bytecode_file);
    if (ret != LEN(magic_sig)) {
        ERR(42); /* failed to read file (magic_sig) */
    }

    if (0 != strncmp("bytecode", magic_sig, LEN(magic_sig))) {
        ERR(43); /* bad bytecode */
    }

    ret = fread(&bytecode_size, sizeof(bytecode_size), 1, bytecode_file);
    if (ret != 1) {
        ERR(44); /* failed to read file (bytecode_size) */
    }

    fseek(bytecode_file, -(bytecode_size + sizeof(magic_sig) + sizeof(bytecode_size)), SEEK_END);

    bytecode = malloc(bytecode_size);
    ret = fread(bytecode, ELEM_SIZE(bytecode), bytecode_size, bytecode_file);
    if (ret != bytecode_size) {
        ERR(45); /* failed to read file (bytecode) */
    }

    fclose(bytecode_file);

    VM__interpret(bytecode, bytecode_size);

    return 0;
}
