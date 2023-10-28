#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "killerMovesTable.h"

const int NUM_KILLER_MOVES_TO_SAVE_PER_DEPTH = 2;
Move** killerMovesTable = NULL;

void initKillerMovesTable() {
    memset(killerMovesTable, 0, MAX_SEARCH_DEPTH * sizeof(Move*));
    for (int i = 0; i < MAX_SEARCH_DEPTH; i++) {
        killerMovesTable[i] = (Move*)malloc(NUM_KILLER_MOVES_TO_SAVE_PER_DEPTH * sizeof(Move));
        memset(killerMovesTable[i], 0, NUM_KILLER_MOVES_TO_SAVE_PER_DEPTH * sizeof(Move));
    }

    if (killerMovesTable == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
}

void clearKillerMovesTable() {
    if (killerMovesTable != NULL) {
        for (int i = 0; i < MAX_SEARCH_DEPTH; i++) {
            free(killerMovesTable[i]);
        }
        free(killerMovesTable);
        killerMovesTable = NULL;
    }
}

void saveKillerMove(Move killerMove) {

}