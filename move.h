#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"
#include <stdbool.h>

typedef struct {
    int from;
    int to;
    int prom;
    char pieceTo;
} Move;

extern const Move nullMove;

void createMove(int from, int to, int prom, char pieceTo, Move* move);
int parse(const char* c);
void moveToUciMove(const Move *move, char uciMove[6]);
void uciMoveToMove(const char uciMove[6], Move *move, bool isWhite);

#endif //SUNFISH_C_MOVE_H
