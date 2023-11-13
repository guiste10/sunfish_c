#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tpMove.h"

TpMoveEntry* tpMove = NULL;

void initTpMove() {
    tpMove = (TpMoveEntry*)malloc(sizeof(TpMoveEntry) * TP_MOVE_SIZE);
    memset(tpMove, 0, sizeof(TpMoveEntry) * TP_MOVE_SIZE);
}

void clearTpMove() {
    if (tpMove != NULL) {
        free(tpMove);
        tpMove = NULL;
    }
}

unsigned int getTpMoveIndexFromHash(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TP_MOVE_SIZE_LOG2) - 1));
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