#ifndef SUNFISH_C_DEBUG_H
#define SUNFISH_C_DEBUG_H

#include "move.h"

void printIntArray(const int* arr, int size);
void printCharArray(const char* arr, int size);
void printMove(Move move, char board[]);
void findBestMoveTimeStamped();
extern const char debugBoard[SIZE];
#endif //SUNFISH_C_DEBUG_H
