
#ifndef SUNFISH_C_SEARCH_H
#define SUNFISH_C_SEARCH_H

#include "position.h"
#define MAX_PV_DEPTH 100


typedef struct {
    int moveCount;  // Number of moves in the line.
    Move moves[MAX_PV_DEPTH];  // The line.
} Line;

void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite);

#endif //SUNFISH_C_SEARCH_H
