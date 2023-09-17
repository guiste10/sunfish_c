#include "move.h"
#include "chessBoard.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void createMove(int i, int j, int prom, Move* move){
    move->from = i;
    move->to = j;
    move->prom = prom;
}

int parse(const char* c) {
    int file = c[0] - 'a';
    int rank = c[1] - '1';
    return A1 + file - 10 * rank;
}

void render(int index, char* result) {
    int rank, file;

    file = (H1 - index) % 10;
    rank = (H1 - index) / 10;

    result[0] = (char)('h' - file);
    result[1] = (char)('1' + rank);
}

void moveToUciMove(const Move *move, char uciMove[6]) {
    int i = move->from;
    int j = move->to;
    char prom = PIECES[move->prom];
    render(i, &uciMove[0]);
    render(j, &uciMove[2]);
    uciMove[4] = prom;
    uciMove[5] = '\0';
}

void uciMoveToMove(const char uciMove[6], Move *move) {
    int i, j;
    int prom;
    char from[3], to[3];
    char uciProm = *(uciMove+4);
    strncpy(from, uciMove, 2);
    from[2] = '\0';
    strncpy(to, uciMove + 2, 2);
    to[2] = '\0';
    i = parse(from);
    j = parse(to);
    prom = uciProm == '\0' ? NO_PROMOTION : indexOf(PIECES, toupper(uciProm));
    createMove(i, j, prom, move);
}