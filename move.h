//
// Created by neiringu on 28-05-23.
//

#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H
typedef struct {
    int i;
    int j;
    char prom;
} Move;

Move* createMove(int i, int j, char prom);
char* render(int i);


#endif //SUNFISH_C_MOVE_H
