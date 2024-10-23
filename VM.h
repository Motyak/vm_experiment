#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>

enum OpCode {
    OP_RETURN = 0
};

enum InterpretResult {
    INTERPRET_ERR = 0,
    INTERPRET_OK = 1
};

enum InterpretResult VM__interpret(const uint8_t*, size_t);

#endif /* VM_H */
