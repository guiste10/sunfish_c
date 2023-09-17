#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"
#include <stdbool.h>

typedef struct {
    int from;
    int to;
    int prom;
} Move;

void createMove(int i, int j, int prom, Move* move);
int parse(const char* c);
void moveToUciMove(const Move *move, char uciMove[6]);
void uciMoveToMove(const char uciMove[6], Move *move);
void moveListToUciString(bool isWhite, Move* moves, int moveCount, char uciMoves[]);

#endif //SUNFISH_C_MOVE_H
