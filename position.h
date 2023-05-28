//
// Created by neiringu on 28-05-23.
//

#ifndef SUNFISH_C_POSITION_H
#define SUNFISH_C_POSITION_H

#include "arraylist.h"
#include "map.h"
#include <stdbool.h>

typedef struct {
    char *board;
    int score;
    bool wc[2];
    bool bc[2];
    bool ep;
    bool kp;
} Position;

Position* initPosition();

ArrayList* gen_moves(Position * position, Map* directions);
#endif //SUNFISH_C_POSITION_H
