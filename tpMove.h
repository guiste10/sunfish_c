
#ifndef SUNFISH_C_TPMOVE_H
#define SUNFISH_C_TPMOVE_H

#include <stdint.h>
#include "position.h"
// todo update size in MB/GB below based on entry
#define TABLE_SIZE_LOG2 25 // Use a table size of 2^20 = 20MB and 1 million entries, if 25 then 600MB and 33.5 million entries, if 27 then 2.57GB and 134 million entries
#define TABLE_SIZE (1 << TABLE_SIZE_LOG2) // Calculate table size as a power of 2

typedef struct {
    uint64_t hash;
    Move bestMove;
} TpMoveEntry;

extern TpMoveEntry* tpMove;

void initTpMove();

void clearTpMove();

TpMoveEntry* lookupTpMove(uint64_t hash);

void saveScore(uint64_t hash, Move bestMove);
#endif //SUNFISH_C_TPMOVE_H
