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
    int rank, file;

    file = (H1 - index) % 10;
    rank = (H1 - index) / 10;

    result[0] = (char)('h' - file);
    result[1] = (char)('1' + rank);
    result[2] = '\0';
}

int parse(const char* c) {
    int file = c[0] - 'a';
    int rank = c[1] - '1';
    return A1 + file - 10 * rank;
}