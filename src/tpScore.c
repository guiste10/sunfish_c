#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpScore.h"

TpScoreEntry** tpScore = NULL;

void initTpScore() {
    tpScore = (TpScoreEntry**)malloc(MAX_SEARCH_DEPTH * sizeof(TpScoreEntry*));
    size_t totalSizeForDepth =  TP_SCORE_NUM_HASHES_LOW_DEPTH * 2 * sizeof(TpScoreEntry);
    for(int depth=0; depth <= MAX_SEARCH_DEPTH; ++depth) {
        tpScore[depth] = (TpScoreEntry*) malloc(totalSizeForDepth);
        memset(tpScore[depth], 0, totalSizeForDepth);
        if(depth == HIGHEST_LOW_DEPTH) {
            totalSizeForDepth = sizeof(TpScoreEntry) * TP_SCORE_NUM_HASHES_HIGH_DEPTH * 2;
        }
    }
}

void clearTpScore() {
    if (tpScore != NULL) {
        for(int depth=0; depth <= MAX_SEARCH_DEPTH; ++depth) {
            free(tpScore[depth]);
        }
        free(tpScore);
        tpScore = NULL;
    }
}

unsigned int getTpScoreIndexFromHash(uint64_t hash, int depth) {
    int numHashes = depth > HIGHEST_LOW_DEPTH ? TP_SCORE_NUM_HASHES_HIGH_DEPTH : TP_SCORE_NUM_HASHES_LOW_DEPTH;
    return (unsigned int)(hash & (numHashes - 1));
}

TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove) {
    unsigned int index = getTpScoreIndexFromHash(hash, depth);
    TpScoreEntry* entry = &(&(tpScore[depth])[index])[canNullMove ? 1 : 0];
    return entry->hash == hash ? entry : NULL;
}

void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound) {
    unsigned int index = getTpScoreIndexFromHash(hash, depth);
    TpScoreEntry* entry = &(&(tpScore[depth])[index])[canNullMove ? 1 : 0];
    entry->hash = hash;
    entry->lowerBound = lowerBound;
    entry->upperBound = upperBound;
}