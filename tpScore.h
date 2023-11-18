
#ifndef SUNFISH_C_TPSCORE_H
#define SUNFISH_C_TPSCORE_H

#include <stdint.h>
#include "position.h"

#define TP_SCORE_NUM_HASHES_HIGH_DEPTH_LOG2 21 // 2^21 => 2 million entries => 2million x 16 bytes x 8depths x 2 = 512MB, to store scores from depth 16 to 9 included
#define TP_SCORE_NUM_HASHES_HIGH_DEPTH (1 << TP_SCORE_NUM_HASHES_HIGH_DEPTH_LOG2)
#define TP_SCORE_NUM_HASHES_LOW_DEPTH_LOG2 23 // 2^24 => 16.5million million entries => 16.5million x 16 bytes x 9depths x 2 = 4.75GB, for depth 8 to 0 included
#define TP_SCORE_NUM_HASHES_LOW_DEPTH (1 << TP_SCORE_NUM_HASHES_LOW_DEPTH_LOG2)
#define HIGHEST_LOW_DEPTH 8 // Fewer hashes need to be stored at higher depths

typedef struct { // 16 bytes
    uint64_t hash;
    int lowerBound;
    int upperBound;
} TpScoreEntry;

extern TpScoreEntry** tpScore; // indexed by hash, depth and canNullMove

void initTpScore();
void clearTpScore();
TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove);
void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound);
#endif //SUNFISH_C_TPSCORE_H
