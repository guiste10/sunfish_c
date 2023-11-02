#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "transpositionTable.h"

TranspositionEntry* transpositionTable = NULL;

const int LOWER = 0;
const int EXACT = 1;
const int UPPER = 2;

void initTranspositionTable() {
    transpositionTable = (TranspositionEntry*)malloc(sizeof(TranspositionEntry) * (1 << TABLE_SIZE_LOG2));

    if (transpositionTable == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    memset(transpositionTable, 0, sizeof(TranspositionEntry) * (1 << TABLE_SIZE_LOG2));
}

void clearTranspositionTable() {
    if (transpositionTable != NULL) {
        free(transpositionTable);
        transpositionTable = NULL;
    }
}

// Hash function to map a position to an index in the transposition table
unsigned int hashFunction(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TABLE_SIZE_LOG2) - 1));
}

TranspositionEntry* lookupTT(uint64_t hash) {
    unsigned int index = hashFunction(hash);
    TranspositionEntry* entry = &transpositionTable[index];

    if (entry->hash == hash) {
        return entry; // Found a matching entry
    } else {
        return NULL; // No matching entry found, TT will be full and unusable if we don't clear it after every search
    }
}

void saveScore(uint64_t hash, int depth, int lowerBound, int upperBound, Move bestMove, int currentPly) {
    unsigned int index = hashFunction(hash);

    TranspositionEntry* entry = &transpositionTable[index];

    // Store the entry if it's deeper
    // or if existing entry is too old then and replace the entry (and don't check for hash equality)
    if (depth > entry->depth || currentPly > (entry->plyStored + 15)) {
        entry->hash = hash;
        entry->depth = depth;
        entry->lowerBound = lowerBound;
        entry->upperBound = upperBound;
        entry->bestMove = bestMove;
    }
}