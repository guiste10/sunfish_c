#include "killerMovesTable.h"

Move killerMovesTable[MAX_SEARCH_DEPTH][NUM_KILLER_MOVES_PER_DEPTH];

void initKillerMovesTable() {
    for (int i = 0; i < MAX_SEARCH_DEPTH; i++) {
        for (int j = 0; j < NUM_KILLER_MOVES_PER_DEPTH; j++) {
            killerMovesTable[i][j] = nullMove;
        }
    }
}

void saveAsKillerMove(Move* cutoffMove, int depth, int ep, char board[]) {
    if(cutoffMove->moveType != nullType && !isCapture(cutoffMove, board, ep)) {
        Move* storedKillerMoves = killerMovesTable[depth];
        if(!(equalMoves(&storedKillerMoves[0], cutoffMove) || equalMoves(&storedKillerMoves[1], cutoffMove))) {
            storedKillerMoves[1] = storedKillerMoves[0];
            storedKillerMoves[0] = *cutoffMove;
        }
    }
}

bool isKillerType(int depth, Move *move) {
    if(move->moveType == nonCaptureType) {
        for (int killerMove = 0; killerMove < NUM_KILLER_MOVES_PER_DEPTH; killerMove++) {
            if (equalMoves(move, &killerMovesTable[depth][killerMove])) {
                return true;
            }
        }
    }
    return false;
}