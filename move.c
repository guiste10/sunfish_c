//
// Created by neiringu on 28-05-23.
//

#include <malloc.h>
#include "move.h"
Move* createMove(int i, int j, char prom) {
    Move* move = malloc(sizeof(Move));
    move->i = i;
    move->j = j;
    move->prom = prom;
    return move;
}