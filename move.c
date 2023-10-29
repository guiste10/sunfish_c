#include "move.h"
#include "chessBoard.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int nullType = -1;
const int unknownType = 0;
const int pvType = 1;
const int promotionType = 2;
const int winningCaptureType = 3;
const int equalCaptureType = 4;
const int killerType = 5; // non capturing!
const int nonCaptureType = 6;
const int losingCaptureType = 7;

const Move nullMove = {nullType};

char* currentBoard;

void createMove(int from, int to, int prom, char pieceTo, Move* move){
    move->from = from;
    move->to = to;
    move->prom = prom;
    move->pieceTo = pieceTo;
    move->moveType = unknownType;
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

bool equalMoves(const Move* moveA, const Move* moveB) {
    return moveA->from == moveB->from &&
    moveA->to == moveB->to &&
    moveA->prom == moveB->prom &&
    moveA->pieceTo == moveB->pieceTo;
}


int compareMoves(const void* x, const void* y) {
    Move* moveA = (Move*)x;
    Move* moveB = (Move*)y;
    if(moveA->moveType != moveB->moveType) {
        return moveA->moveType - moveB->moveType; // moveType closer to 0 is ordered first
    }
    return moveB->moveValue - moveA->moveValue;
}

void sortMoves(Move moves[], int numMoves, char *board) {
    currentBoard = board;
    qsort(moves, numMoves, sizeof(Move), compareMoves);
}