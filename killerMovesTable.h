
#ifndef SUNFISH_C_KILLERMOVESTABLE_H
#define SUNFISH_C_KILLERMOVESTABLE_H

#include <stdint.h>
#include "move.h"

extern const int NUM_KILLER_MOVES_TO_SAVE_PER_DEPTH;
extern Move** killerMovesTable;

void initKillerMovesTable();

void clearKillerMovesTable();

void saveKillerMove(Move killerMove);

#endif //SUNFISH_C_KILLERMOVESTABLE_H
