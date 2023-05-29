//
// Created by neiringu on 28-05-23.
//

#include <malloc.h>
#include "move.h"
#include "chessBoard.h"

Move* createMove(int i, int j, char prom) {
    Move* move = malloc(sizeof(Move));
    move->i = i;
    move->j = j;
    move->prom = prom;
    return move;
}


char* render(int index) {
    int rank, fil;
    char* result = malloc(sizeof(char) * 3);  // Allocate memory for the result (e.g., "a1")

    fil = (H1 - index) % 10;
    rank = (H1 - index) / 10;

    result[0] = (char)('h' - fil);
    result[1] = (char)('1' + rank);
    result[2] = '\0';  // Null-terminate the string

    return result;
}