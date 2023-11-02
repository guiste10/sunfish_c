
#ifndef SUNFISH_C_TRANSPOSITIONTABLE_H
#define SUNFISH_C_TRANSPOSITIONTABLE_H

#include <stdint.h>
#include "position.h"

#define TABLE_SIZE_LOG2 27 // Use a table size of 2^20 = 20MB and 1 million entries, if 25 then 600MB and 33.5 million entries, if 27 then 2.57GB and 134 million entries
#define TABLE_SIZE (1 << TABLE_SIZE_LOG2) // Calculate table size as a power of 2

typedef struct {
    uint64_t hash;
    int depth;
    int lowerBound;
    int upperBound;
    int plyStored;
    Move bestMove;
} TranspositionEntry;

extern TranspositionEntry* transpositionTable;

extern const int LOWER;
extern const int EXACT;
extern const int UPPER;

void initTranspositionTable();

void clearTranspositionTable();

TranspositionEntry* lookupTT(uint64_t hash);

void saveScore(uint64_t hash, int depth, int lowerBound, int upperBound, Move bestMove, int currentPly);
#endif //SUNFISH_C_TRANSPOSITIONTABLE_H
