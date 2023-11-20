#ifndef SUNFISH_C_SEARCH_H
#define SUNFISH_C_SEARCH_H

#include "position.h"

extern int numNodes;

Move searchBestMove(Position* position, int timeLeftMs);
int isRepetition(const Position *position);
int bound(Position *position, int gamma, int depth, bool canNullMove);
#endif //SUNFISH_C_SEARCH_H
