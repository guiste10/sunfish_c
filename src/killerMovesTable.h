#ifndef SUNFISH_C_KILLERMOVESTABLE_H
#define SUNFISH_C_KILLERMOVESTABLE_H

#include <stdint.h>
#include "move.h"
void initKillerMovesTable();
void saveAsKillerMove(Move* cutoffMove, int depth, int ep, int board[]);
bool isKillerType(int depth, int* board, int ep, Move *move);
#endif //SUNFISH_C_KILLERMOVESTABLE_H