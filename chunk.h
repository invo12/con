#ifndef conq_chunk_h
#define conq_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_ADD,
    OP_CONSTANT,
    OP_DIVIDE,
    OP_MULTIPLY,
    OP_NEGATE,
    OP_RETURN,
    OP_SUBSTRACT
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte, int line);

void freeChunk(Chunk *chunk);

int addConstant(Chunk *chunk, Value value);

#endif
