#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpScore.h"

TpScoreEntry* tpScore = NULL;

void initTpScore() {
    size_t totalSize = sizeof(TpScoreEntry) * TP_SCORE_SIZE * MAX_SEARCH_DEPTH * 2;
    tpScore = (TpScoreEntry*)malloc(totalSize);

    if (tpScore == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    memset(tpScore, 0, totalSize);
}

void clearTpScore() {
    // Check if the array has been allocated
    if (tpScore != NULL) {
        // Free the allocated memory
        free(tpScore);
        // Set the pointer to NULL to avoid using it after deallocation
        tpScore = NULL;
    }
}

// Hash function to map a position to an index in the transposition table
unsigned int getTpScoreIndexFromHash(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TP_SCORE_SIZE_LOG2) - 1));
}

TpScoreEntry* lookupTpScore(uint64_t hash, int depth, bool canNullMove) {
    unsigned int index = getTpScoreIndexFromHash(hash);
    TpScoreEntry* entry = &(&(&tpScore[index])[depth])[canNullMove ? 1 : 0];

    if (entry->hash == hash) {
        return entry; // Found a matching entry
    } else {
        return NULL; // No matching entry found, TT will be full and unusable if we don't clear it after every search
    }
}

void saveScore(uint64_t hash, int depth, bool canNullMove, int lowerBound, int upperBound) {
    unsigned int index = getTpScoreIndexFromHash(hash);

    TpScoreEntry* entry = &(&(&tpScore[index])[depth])[canNullMove ? 1 : 0];

    entry->hash = hash;
    entry->lowerBound = lowerBound;
    entry->upperBound = upperBound;
}