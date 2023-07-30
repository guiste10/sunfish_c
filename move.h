#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"
#include <stdbool.h>

typedef struct {
    int i;
    int j;
    int prom;
} Move;

void createMove(int i, int j, int prom, Move* move);
int parse(const char* c);
void moveToUciMove(bool isWhite, const Move *move, char uciMove[6]);
void uciMoveToMove(bool isWhite, const char uciMove[6], Move *move);

#endif //SUNFISH_C_MOVE_H
