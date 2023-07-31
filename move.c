#include "move.h"
#include "chessBoard.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void createMove(int i, int j, int prom, Move* move){
    move->i = i;
    move->j = j;
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

void moveToUciMove(bool isWhite, const Move *move, char uciMove[6]) {
    int i = move->i;
    int j = move->j;
    char prom = PIECES[move->prom];
    if (!isWhite) {
        i = 119 - i;
        j = 119 - j;
    }
    render(i, &uciMove[0]);
    render(j, &uciMove[2]);
    uciMove[4] = prom;
    uciMove[5] = '\0';
}

void moveListToUciString(bool isWhite, Move* moves, int moveCount, char uciMoves[]) {
    strcpy(uciMoves, "");
    for(int i = 0; i < moveCount; i++){
        char uciMove[6];
        if(i != 0){
            strcat(uciMoves, " ");
        }
        moveToUciMove(isWhite, &moves[i], uciMove);
        strcat(uciMoves, uciMove);
        isWhite = !isWhite;
    }
}

void uciMoveToMove(bool isWhite, const char uciMove[6], Move *move) {
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
    if (!isWhite) {
        i = 119 - i;
        j = 119 - j;
    }
    createMove(i, j, prom, move);
}