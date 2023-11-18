
#ifndef SUNFISH_C_TPSCORE_H
#define SUNFISH_C_TPSCORE_H

#include <stdint.h>
#include "position.h"

#define TP_SCORE_SIZE_LOG2 20 // 2^20 => 1 million entries x 16 bytes x maxdepth x 2 = 512MB, 2^25 => 33.5 million entries x 16 bytes x 16 x 2 = 16.8GB,
#define TP_SCORE_SIZE (1 << TP_SCORE_SIZE_LOG2) // Calculate table size as a power of 2

typedef struct { // 16 bytes
    uint64_t hash;
    int lowerBound;
    int upperBound;
} TpScoreEntry;

extern TpScoreEntry* tpScore; // indexed by hash, depth and canNullMove

void initTpScore();
void clearTpScore();
TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove);
void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound);
#endif //SUNFISH_C_TPSCORE_H
