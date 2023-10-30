#include "killerMovesTable.h"

Move killerMovesTable[MAX_SEARCH_DEPTH][NUM_KILLER_MOVES_PER_DEPTH] = {
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
        {{0},{0}},
};


void saveKillerMove(Move* cutoffMove, int depth) {
    if(cutoffMove->pieceTo == '.') { // only save non-captures and en passant
        Move* storedKillerMoves = killerMovesTable[depth];
        if(!(equalMoves(&storedKillerMoves[0], cutoffMove) || equalMoves(&storedKillerMoves[1], cutoffMove))) {
            storedKillerMoves[1] = storedKillerMoves[0];
            storedKillerMoves[0] = *cutoffMove;
        }
    }
}