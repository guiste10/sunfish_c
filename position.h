//
// Created by neiringu on 28-05-23.
//

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
    int kp; // square where the king has passed but not stopped during castling
} Position;

Position* initPosition();

ArrayList* genMoves(Position * position);

void doMove(Position* position, Move* move, char* newBoard);
#endif //SUNFISH_C_POSITION_H
