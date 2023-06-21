#ifndef SUNFISH_C_POSITION_H
#define SUNFISH_C_POSITION_H
#include "arraylist.h"
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

Position* initPosition(char* boardSrc);

Position* duplicatePosition(Position* source);

ArrayList* genMoves(Position * position);

Position* doMove(Position* position, Move* move);

void rotate(Position* position, bool nullMove);
#endif //SUNFISH_C_POSITION_H
