
#ifndef SUNFISH_C_SEARCH_H
#define SUNFISH_C_SEARCH_H

#include "position.h"

extern int numNodes;
void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite);

#endif //SUNFISH_C_SEARCH_H
