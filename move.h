#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"

typedef struct {
    int i;
    int j;
    int prom;
} Move;

void addMove(int i, int j, int prom, Move* move);
void render(int index, char* result);
int parse(const char* c);

#endif //SUNFISH_C_MOVE_H
