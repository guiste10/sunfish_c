#ifndef SUNFISH_C_POSITION_H
#define SUNFISH_C_POSITION_H

#include "arraylist.h"
#include "map.h"
#include "move.h"
#include <stdbool.h>

typedef struct {
    char *board;
    int score;
    bool wc[2];
    bool bc[2];
    int ep;
    int kp; // square where the king has walked but not stopped during castling (e.g. f1 or d1 for white)
} Position;

void initPosition(Position* position);

ArrayList* genMoves(Position * position);

void doMove(Position* position, Move* move, Position* newPosition, char* newBoard);
#endif //SUNFISH_C_POSITION_H
