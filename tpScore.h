
#ifndef SUNFISH_C_TPSCORE_H
#define SUNFISH_C_TPSCORE_H

#include <stdint.h>
#include "position.h"

#define TP_SCORE_SIZE_LOG2 20 // Use a table size of 2^20 = 20MB and 1 million entries, if 25 then 600MB and 33.5 million entries, if 27 then 2.57GB and 134 million entries
#define TP_SCORE_SIZE (1 << TP_SCORE_SIZE_LOG2) // Calculate table size as a power of 2

typedef struct {
    uint64_t hash;
    int lowerBound;
    int upperBound;
    int plyStored;
} TpScoreEntry;

extern TpScoreEntry* tpScore; // indexed by hash, depth and canNullMove

void initTpScore();

void clearTpScore();

TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove);

void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound);
#endif //SUNFISH_C_TPSCORE_H
