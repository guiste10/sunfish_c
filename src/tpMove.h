#ifndef SUNFISH_C_TPMOVE_H
#define SUNFISH_C_TPMOVE_H
#include <stdint.h>
#include "position.h"
#define TP_MOVE_SIZE_LOG2 24 // 2^20 = 1 million entries = 28MB, 2^25 then 33.5 million entries = 938 MB, if 27 then 134 million entries = 3.75GB
#define TP_MOVE_SIZE (1 << TP_MOVE_SIZE_LOG2) // Calculate table size as a power of 2

typedef struct { // 28 bytes per TpMoveEntry
    uint64_t hash;
    Move bestMove;
} TpMoveEntry;

extern TpMoveEntry* tpMove;

void initTpMove();
void clearTpMove();
Move* lookupTpMove(uint64_t hash);
void saveMove(uint64_t hash, Move bestMove);
#endif //SUNFISH_C_TPMOVE_H
