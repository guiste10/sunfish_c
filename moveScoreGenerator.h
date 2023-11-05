
#ifndef SUNFISH_C_MOVESCOREGENERATOR_H
#define SUNFISH_C_MOVESCOREGENERATOR_H

#include "move.h"
#include "position.h"

extern const int LAST;
extern const int STOP;

// returns the next step id
int getNextMoveScoreLazy(int step, Position* position, int gamma, int depth, bool canNull,
                         int valLower, Position* positionBackup, Move* actualMoves, int* numActualMoves,
                         int *moveIndex, Move* moveToYield, int* scoreToYield);
#endif //SUNFISH_C_MOVESCOREGENERATOR_H
