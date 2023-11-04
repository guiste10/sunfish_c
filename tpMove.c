#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpMove.h"

TpMoveEntry* tpMove = NULL;

void initTpMove() {
    tpMove = (TpMoveEntry*)malloc(sizeof(TpMoveEntry) * (1 << TABLE_SIZE_LOG2));

    if (tpMove == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    memset(tpMove, 0, sizeof(TpMoveEntry) * (1 << TABLE_SIZE_LOG2));
}

void clearTpMove() {
    if (tpMove != NULL) {
        free(tpMove);
        tpMove = NULL;
    }
}

// Hash function to map a position to an index in the transposition table
unsigned int hashFunction(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TABLE_SIZE_LOG2) - 1));
}

TpMoveEntry* lookupTpMove(uint64_t hash) {
    unsigned int index = hashFunction(hash);
    TpMoveEntry* entry = &tpMove[index];

    if (entry->hash == hash) {
        return entry; // Found a matching entry
    } else {
        return NULL; // No matching entry found, TT will be full and unusable if we don't clear it after every search
    }
}

void saveMove(uint64_t hash, Move bestMove) {
    unsigned int index = hashFunction(hash); // todo verify if check on depth needed to save best move?

    TpMoveEntry* entry = &tpMove[index];

    entry->hash = hash;
    entry->bestMove = bestMove;
}