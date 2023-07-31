#ifndef SUNFISH_C_DEBUG_H
#define SUNFISH_C_DEBUG_H

#include "move.h"

void printIntArray(const int* arr, int size);
void printCharArray(const char* arr, int size);
void printMove(Move move, char board[]);
void findBestMoveTimeStamped(char* boardToUse);
void findBestMoveFromUciPosition(char* uciPosition);
extern const char debugBoard[SIZE];
extern const char debugBoard2[SIZE];
extern const char debugBoard3[SIZE];
extern const char randomBoard[SIZE];
#endif //SUNFISH_C_DEBUG_H
