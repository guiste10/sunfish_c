#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "search.h"


int numNodes = 0;
char* currentBoard;
bool isEndGame = false;

int negamax(Position* position, int depth, int initDepth, int alpha, int beta, bool doPatCheck, bool canNullMove, Move moves[], Line * pline);

bool onlyKingMoves(Move moves[MAX_BRANCHING_FACTOR], int numMoves, const char *board) {
    for (int i=0; i<numMoves; i++){
        if(*(board + moves[i].i) != 'K'){
            return false;
        }
    }
    return true;
}

bool isKingInCheck(Position *position) {
    Position target;
    char targetBoard[SIZE];
    Position* duplicatePos = duplicatePosition(position, &target, targetBoard);
    rotate(duplicatePos, false);
    Move opponentMoves[MAX_BRANCHING_FACTOR];
    Line uselessPvLine;
    int score = negamax(duplicatePos, 1, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &uselessPvLine);
    return score >= MATE_LOWER;
}

bool allKingMovesLeadToDeath(Position *position, int numMoves, Move kingMoves[MAX_BRANCHING_FACTOR]) {
    for (int i=0; i < numMoves; i++){
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = &kingMoves[i];
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Line uselessPvLine;
        int score = negamax(newPosition, 1, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &uselessPvLine);
        if (score < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}

bool isPat(Position* position, int numMoves, Move moves[MAX_BRANCHING_FACTOR]) {
    if(onlyKingMoves(moves, numMoves, position->board)) {
        if(!isKingInCheck(position)){
            return allKingMovesLeadToDeath(position, numMoves, moves);
        }
    }
    return false;
}

int compareMoves(const void* a, const void* b) {
    Move* moveA = (Move*)a;
    Move* moveB = (Move*)b;

    char pieceToA = currentBoard[moveA->j];
    char pieceToB = currentBoard[moveB->j];
    if(pieceToA != '.' && pieceToB != '.'){
        char pieceFromA = currentBoard[moveA->i];
        char pieceFromB = currentBoard[moveB->i];
        return (pieceValues[pieceIndexes[pieceToB]] - pieceValues[pieceIndexes[pieceFromB]]) -
               (pieceValues[pieceIndexes[pieceToA]] - pieceValues[pieceIndexes[pieceFromA]]); // prioritize winning captures (e.g. pawn takes queen)
    }
    else if(pieceToA != '.'){
        return -1;
    }
    else if(pieceToB != '.'){
        return 1;
    }
    return 0;
}

int negamax(Position* position, int depth, int initDepth, int alpha, int beta, bool doPatCheck, bool canNullMove, Move moves[], Line * pline) {
    numNodes++;
    Line line;
    if (position->score <= -MATE_LOWER) {
        pline->moveCount = 0;
        return -MATE_UPPER;
    }
    if (depth == 0) {
        pline->moveCount = 0;
        return position->score;
    }

    int numMoves = genMoves(position, moves);
    if(doPatCheck && isPat(position, numMoves, moves) == true) {
        pline->moveCount = 0;
        return 0;
    }

    if(canNullMove && depth > 3 && !isEndGame){
        Position target;
        char targetBoard[SIZE];
        Position* duplicatePos = duplicatePosition(position, &target, targetBoard);
        rotate(duplicatePos, true);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Line uselessPvLine;
        int score = -negamax(duplicatePos, depth - 3, depth - 3, -beta, -alpha, false, false, opponentMoves, &uselessPvLine);
        if(score >= beta){
            return beta;
        }
    }

    currentBoard = position->board;
    qsort(moves, numMoves, sizeof(Move), compareMoves);
    for (int i = 0; i < numMoves; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = &moves[i];
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move opponentMoves[MAX_BRANCHING_FACTOR];

        int score = -negamax(newPosition, depth - 1, initDepth, -beta, -alpha, true, true, opponentMoves, &line);
        if (score >= MATE_LOWER) {
            score--; // winning mate found, add one point penalty per depth
        } else if (score <= -MATE_LOWER) {
            score++; // losing mate found, add one point penalty per depth
        }

        if (score >= beta) {
            return beta; // Beta cutoff
        }
        if (score > alpha) {
            alpha = score;
            pline->moves[0] = *move; // add best move and pv from child
            memcpy(pline->moves + 1, line.moves, line.moveCount * sizeof(Move));
            pline->moveCount = line.moveCount + 1;
        }
        alpha = (alpha > score) ? alpha : score;
    }
    return alpha;
}

void setIsEndGame(const char* board) {
    int numFriendlyPieces = 0;
    for(int square = 0; square < SIZE ; square++) {
        char piece = board[square];
        if(piece != '.' && isupper(piece) && piece != 'P'){
            numFriendlyPieces++;
        }
    }
    isEndGame = numFriendlyPieces <= 2;
}

void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite) {
    setIsEndGame(position->board);
    double timeTakenMs;
    int score;
    clock_t start = clock();
    bool isMate = false;
    bool canFurtherIncreaseDepth = true;
    const int minDepth = 6;
    const int maxDepth = 6;
    for(int depth = 5; depth == 5; depth++){
    //for(int depth = 1; !isMate && (depth <= minDepth || canFurtherIncreaseDepth); depth++){
        Move moves[MAX_BRANCHING_FACTOR];
        Line pv;
        numNodes = 0;
        score = negamax(position, depth, depth, -INT_MAX, INT_MAX, false, false, moves, &pv);
        timeTakenMs = clock() - start;
        double nps = timeTakenMs == 0.0 ? 0 : numNodes/(timeTakenMs/1000.0);
        printf("info depth %d time %.2f nps %.2f\n", depth, timeTakenMs, nps);
        char pvString[1000];
        moveListToUciString(isWhite, pv.moves, pv.moveCount, pvString);
        printf("info pv %s score cp %d\n", pvString, score);
        fflush(stdout);
        isMate = abs(score) >= MATE_LOWER;
        canFurtherIncreaseDepth = timeTakenMs < 800.0 && timeLeftMs > 10000;
        *bestMove = pv.moves[0];
    }
}