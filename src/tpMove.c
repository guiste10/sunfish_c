#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpMove.h"

TpMoveEntry* tpMove = NULL;

void initTpMove() {
    size_t totalSize = sizeof(TpMoveEntry) * TP_MOVE_SIZE;
    tpMove = (TpMoveEntry*)malloc(totalSize);
    memset(tpMove, 0, totalSize);
}

void clearTpMove() {
    if (tpMove != NULL) {
        free(tpMove);
        tpMove = NULL;
    }
}

unsigned int getTpMoveIndexFromHash(uint64_t hash) {
    return (unsigned int)(hash & (TP_MOVE_SIZE - 1));
}

Move* lookupTpMove(uint64_t hash) {
    unsigned int index = getTpMoveIndexFromHash(hash);
    TpMoveEntry* entry = &tpMove[index];
    return entry->hash == hash ? &entry->bestMove : NULL;
}

void saveMove(uint64_t hash, Move bestMove) {
    unsigned int index = getTpMoveIndexFromHash(hash);
    TpMoveEntry* entry = &tpMove[index];
    entry->hash = hash;
    entry->bestMove = bestMove;
}