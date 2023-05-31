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

void render(int index, char* result) {
    int rank, fil;

    fil = (H1 - index) % 10;
    rank = (H1 - index) / 10;

    result[0] = (char)('h' - fil);
    result[1] = (char)('1' + rank);
    result[2] = '\0';  // Null-terminate the string
}

void printMove(Move move, char board[]) {
    char from[3];  // Local character array to store the "from" position
    char to[3];  // Local character array to store the "to" position

    render(move.i, from);
    render(move.j, to);

    printf("Move %c from i = %s to j = %s, prom = %c\n", board[move.i], from, to, move.prom);

    fflush(stdout);  // Flush the output stream
}
