#include "VM.h"

#include <stdio.h>

enum InterpretResult VM__interpret(const uint8_t* bytecode, size_t bytecode_size) {
    const uint8_t* ip = bytecode;

    uint8_t instruction = *ip;
    while (ip < bytecode + bytecode_size) {
        switch (instruction) {
            case OP_RETURN: {
                printf("return\n");
                ip++;
            }
        }
    }

    return INTERPRET_OK;
}
