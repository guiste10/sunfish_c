
#ifndef SUNFISH_C_KILLERMOVESTABLE_H
#define SUNFISH_C_KILLERMOVESTABLE_H

#include <stdint.h>
#include "move.h"

extern Move killerMovesTable[MAX_SEARCH_DEPTH][NUM_KILLER_MOVES_PER_DEPTH];

void saveKillerMove(Move* cutoffMove, int depth);

#endif //SUNFISH_C_KILLERMOVESTABLE_H
