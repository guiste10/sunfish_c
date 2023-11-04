
#ifndef SUNFISH_C_SEARCH_H
#define SUNFISH_C_SEARCH_H

#include "position.h"

Move searchBestMove(Position* position, int timeLeftMs, bool isWhite);
int bound(Position *position, int gamma, int depth, bool canNullMove);
int getNullMoveScore(Position *position, int newGamma, int depth);
#endif //SUNFISH_C_SEARCH_H
