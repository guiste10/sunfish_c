#include "move.h"
#include "chessBoard.h"
#include "utils.h"
#include "killerMovesTable.h"
#include "pieceSquareTables.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int nullType = -1;
const int unknownType = 0;
const int pvType = 1;
const int winningCaptureType = 3;
const int killerType = 2; // non capturing!
const int equalCaptureType = 4;
const int losingCaptureType = 5;
const int promotionType = 6;
const int quietType = 7;

const Move nullMove = {nullType};

char* currentBoard;

void createMove(int from, int to, int prom, char pieceTo, Move* move){
    move->from = from;
    move->to = to;
    move->prom = prom;
    move->pieceTo = pieceTo;
    move->moveType = unknownType;
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

void flagMovesWithType(Move *moves, int numMoves, int depth, bool hasBestMoveTT, Move *bestMoveTT){
    Move* move;
    for (int bestTTMoveIndex=0; bestTTMoveIndex < numMoves; bestTTMoveIndex++) {
        move = &moves[bestTTMoveIndex];
        if(hasBestMoveTT && equalMoves(move, bestMoveTT)) {
            move->moveType = pvType; // pv move will first move in the moves lost after sorting
            return;
        }
//        for(int killerMove = 0; killerMove < NUM_KILLER_MOVES_TO_SAVE_PER_DEPTH; killerMove++) {
//            if(equalMoves(move, &killerMovesTable[depth][killerMove])) {
//                move->moveType = killerType;
//            }
//        }
    }
}

int compareMoves(const void* x, const void* y) { // todo order losing captures after non captures
    Move* moveA = (Move*)x;
    Move* moveB = (Move*)y;
    if(moveA->moveType == pvType){
        return -1;
    }
    if(moveB->moveType == pvType){
        return 1;
    }
    int promA = moveA->prom;
    int promB = moveB->prom;
    if(promA != NO_PROMOTION && promB != NO_PROMOTION){
        return promB - promA;
    }
    else if(promA != NO_PROMOTION){
        return -1;
    }
    else if(promB != NO_PROMOTION){
        return 1;
    }
    char toPieceA = currentBoard[moveA->to];
    char toPieceB = currentBoard[moveB->to];
    if(toPieceA != '.' && toPieceB != '.'){
        char fromPieceA = currentBoard[moveA->from];
        char fromPieceB = currentBoard[moveB->from];
        return (pieceValues[PIECE_INDEXES_WHITE[toPieceB]] - pieceValues[PIECE_INDEXES_WHITE[fromPieceB]]) -
               (pieceValues[PIECE_INDEXES_WHITE[toPieceA]] - pieceValues[PIECE_INDEXES_WHITE[fromPieceA]]); // prioritize winning captures (e.g. pawn takes queen)
    }
    else if(toPieceA != '.'){
        return -1; // negative number -> move A must be ordered before move B since it is a pieceTo
    }
    else if(toPieceB != '.'){
        return 1;
    }
    char fromPieceA = currentBoard[moveA->from];
    char fromPieceB = currentBoard[moveB->from];
    int pieceIndexA = PIECE_INDEXES[fromPieceA];
    int pieceIndexB = PIECE_INDEXES[fromPieceB];

    int scoreA = PST[pieceIndexA][moveA->to] - PST[pieceIndexB][moveA->from];
    int scoreB = PST[pieceIndexB][moveB->to] - PST[pieceIndexB][moveB->from];

    return isupper(fromPieceA) ? scoreB - scoreA : scoreA - scoreB;
}

void sortMoves(Move moves[], int numMoves, char *board) {
    currentBoard = board;
    qsort(moves, numMoves, sizeof(Move), compareMoves);
}