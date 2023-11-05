#ifndef SUNFISH_C_DEBUG_H
#define SUNFISH_C_DEBUG_H

#include "move.h"

void printIntArray(const int* arr, int size);
void printCharArray(const char* arr, int size);
void findBestMoveFromUciPosition(char* uciPosition);
#endif //SUNFISH_C_DEBUG_H
