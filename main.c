
#include "VM.h"
// #include "mystdio.h"
// #define fseek my_fseek

/* libc */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define ELEM_SIZE(arr) sizeof(arr[0])

#define ERR(exit_code) \
    if (file) { \
        fclose(file); \
    } \
    return exit_code

int main(int argc, char* argv[])
{
    const char* filepath = argc == 2? argv[1] : argv[0];
    FILE* file = NULL;
    char magic_sig[8];
    uint32_t bytecode_size;
    uint8_t* bytecode = NULL;
    size_t ret;

    file = fopen(filepath, "rb");
    if (!file) {
        ERR(41); // failed to open file
    }

    ret = fseek(file, -sizeof(magic_sig) - sizeof(bytecode_size), SEEK_END);
    if (ret == (size_t)-1) {
        ERR(42); // file is too short to conform
    }

    ret = fread(magic_sig, ELEM_SIZE(magic_sig), LEN(magic_sig), file);
    if (ret != LEN(magic_sig)) {
        ERR(43); // failed to read file (magic_sig)
    }

    if (0 != strncmp("bytecode", magic_sig, LEN(magic_sig))) {
        ERR(44); // no magic sig
    }

    ret = fread(&bytecode_size, sizeof(bytecode_size), 1, file);
    if (ret != 1) {
        ERR(45); // failed to read file (bytecode_size)
    }

    ret = fseek(file, -(bytecode_size + sizeof(magic_sig) + sizeof(bytecode_size)), SEEK_END);
    if (ret == (size_t)-1) {
        ERR(46); // incorrect bytecode size
    }

    bytecode = malloc(bytecode_size);
    ret = fread(bytecode, ELEM_SIZE(bytecode), bytecode_size, file);
    if (ret != bytecode_size) {
        ERR(47); // failed to read file (bytecode)
    }

    fclose(file);

    VM__interpret(bytecode, bytecode_size);

    return 0;
}
