#include "killerMovesTable.h"
#include "move.h"

Move killerMovesTable[MAX_SEARCH_DEPTH][NUM_KILLER_MOVES_PER_DEPTH];

void initKillerMovesTable() {
    for (int i = 0; i < MAX_SEARCH_DEPTH; ++i) {
        for (int j = 0; j < NUM_KILLER_MOVES_PER_DEPTH; ++j) {
            killerMovesTable[i][j] = nullMove;
        }
    }
}

void saveAsKillerMove(Move* cutoffMove, int depth, int ep, char board[]) {
    if(!isCapture(cutoffMove, board, ep)) {
        Move* storedKillerMoves = killerMovesTable[depth];
        if(!(equalMoves(&storedKillerMoves[0], cutoffMove) || equalMoves(&storedKillerMoves[1], cutoffMove))) {
            storedKillerMoves[1] = storedKillerMoves[0];
            storedKillerMoves[0] = *cutoffMove;
        }
    }
}

bool isKillerType(int depth, char* board, int ep, Move *move) {
    return !isCapture(move, board, ep) && (equalMoves(move, &killerMovesTable[depth][0]) || equalMoves(move, &killerMovesTable[depth][1]));
}