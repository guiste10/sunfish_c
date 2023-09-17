#ifndef SUNFISH_C_POSITION_H
#define SUNFISH_C_POSITION_H
#include "move.h"
#include "constants.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char *board;
    int score;
    bool wc[2];
    bool bc[2];
    int ep;
    int kp; // square where the king has walked but not stopped during castling (e.g. f1 or d1 for white)
    int isWhite;
    uint64_t hash;
} Position;

void initPosition(Position* position, char* boardToUse);

Position* duplicatePosition(Position* source, Position* target, char* targetBoard);

int genMoves(Position * position, Move moves[MAX_BRANCHING_FACTOR]);

void doMove(Position* position, Move* move);
#endif //SUNFISH_C_POSITION_H
