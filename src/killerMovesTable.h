#ifndef SUNFISH_C_KILLERMOVESTABLE_H
#define SUNFISH_C_KILLERMOVESTABLE_H

#include <stdint.h>
#include "move.h"
void initKillerMovesTable();
void saveAsKillerMove(Move* cutoffMove, int depth, int ep, char board[]);
bool isKillerType(int depth, char* board, int ep, Move *move);
#endif //SUNFISH_C_KILLERMOVESTABLE_H