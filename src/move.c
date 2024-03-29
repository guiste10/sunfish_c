#include "move.h"
#include "chessBoard.h"
#include <string.h>
#include <ctype.h>

const Move nullMove = {NULL_MOVE};

void createMove(int from, int to, int prom, char pieceTo, Move* move){
    move->from = from;
    move->to = to;
    move->prom = prom;
    move->pieceTo = pieceTo;
    move->moveValue = 0;
}

int parseUciSquareToBoardIndex(const char* uciSquare) {
    int file = uciSquare[0] - 'a';
    int rank = uciSquare[1] - '1';
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
    char prom = ALL_PIECES[move->prom];
    render(i, &uciMove[0]);
    render(j, &uciMove[2]);
    uciMove[4] = tolower(prom);
    uciMove[5] = '\0';
}

int indexOf(const char* str, char target) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == target) {
            return i;  // Return the index if the character is found
        }
        i++;
    }
    return -1;
}

void uciMoveToMove(const char uciMove[6], Move *move, bool isWhite) {
    int i, j;
    int prom;
    char from[3], to[3];
    char uciProm = *(uciMove+4);
    strncpy(from, uciMove, 2);
    from[2] = '\0';
    strncpy(to, uciMove + 2, 2);
    to[2] = '\0';
    i = parseUciSquareToBoardIndex(from);
    j = parseUciSquareToBoardIndex(to);
    prom = uciProm == '\0' ? NO_PROMOTION : indexOf(ALL_PIECES, isWhite ? toupper(uciProm) : uciProm);
    createMove(i, j, prom, '.', move);
}

int compareMoves(const void* x, const void* y) {
    Move* moveA = (Move*)x;
    Move* moveB = (Move*)y;
    return moveB->moveValue - moveA->moveValue;
}