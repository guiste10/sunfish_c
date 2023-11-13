#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpScore.h"

TpScoreEntry* tpScore = NULL;

void initTpScore() {
    size_t totalSize = sizeof(TpScoreEntry) * TP_SCORE_SIZE * MAX_SEARCH_DEPTH * 2;
    tpScore = (TpScoreEntry*)malloc(totalSize);
    memset(tpScore, 0, totalSize);
}

void clearTpScore() {
    if (tpScore != NULL) {
        free(tpScore);
        tpScore = NULL;
    }
}

unsigned int getTpScoreIndexFromHash(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TP_SCORE_SIZE_LOG2) - 1));
}

TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove) {
    unsigned int index = getTpScoreIndexFromHash(hash);
    TpScoreEntry* entry = &(&(&tpScore[index])[depth])[canNullMove ? 1 : 0];
    return entry->hash == hash ? entry : NULL;
}

void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound) {
    unsigned int index = getTpScoreIndexFromHash(hash);
    TpScoreEntry* entry = &(&(&tpScore[index])[depth])[canNullMove ? 1 : 0];
    entry->hash = hash;
    entry->lowerBound = lowerBound;
    entry->upperBound = upperBound;
}