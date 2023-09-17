
#ifndef SUNFISH_C_UCI_H
#define SUNFISH_C_UCI_H

#include "position.h"

extern int MAX_ARGS;
void playUci();
void fillArgs(char* line, char* args[MAX_ARGS], int* numArgs);
void setupPositionWithMoveList(Position* position,  char* initialBoardCopy, bool* isWhite, char *uciMoves[1000], int numArgs);

#endif //SUNFISH_C_UCI_H
