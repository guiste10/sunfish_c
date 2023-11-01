#include "killerMovesTable.h"

Move killerMovesTable[MAX_SEARCH_DEPTH][NUM_KILLER_MOVES_PER_DEPTH];

void initKillerMovesTable() {
    for (int i = 0; i < MAX_SEARCH_DEPTH; i++) {
        for (int j = 0; j < NUM_KILLER_MOVES_PER_DEPTH; j++) {
            killerMovesTable[i][j] = nullMove;
        }
    }
}

void saveKillerMove(Move* cutoffMove, int depth) {
    if(cutoffMove->moveType != nullType && cutoffMove->pieceTo == '.') { // only save non-captures (and en passant)
        Move* storedKillerMoves = killerMovesTable[depth];
        if(!(equalMoves(&storedKillerMoves[0], cutoffMove) || equalMoves(&storedKillerMoves[1], cutoffMove))) {
            storedKillerMoves[1] = storedKillerMoves[0];
            storedKillerMoves[0] = *cutoffMove;
        }
    }
}