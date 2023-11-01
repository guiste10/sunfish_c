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
    uint64_t *history;
    int plyIrreversible;
    int currentPly;
} Position;

void initPosition(Position *position, char *boardCopy, char *boardToUse, uint64_t* history);

Position* duplicatePosition(Position* source, Position* target);

int genMoves(Position * position, Move moves[MAX_BRANCHING_FACTOR]);
int value(const Position *position, const Move *move);

void doMove(Position* position, const Move* move);
void undoMove(Position* position, Move* move, Position positionOld);
#endif //SUNFISH_C_POSITION_H
