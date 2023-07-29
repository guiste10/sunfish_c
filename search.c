#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"

const int maxDepth = 6;
int numNodes = 0;
char* currentBoard;

int negamax(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove, Move moves[MAX_BRANCHING_FACTOR], Move* bestMoveToSave);

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
    Move bestChildMove;
    int score = negamax(duplicatePos, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
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
        Move bestChildMove;
        int score = negamax(newPosition, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
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

int negamax(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove, Move moves[MAX_BRANCHING_FACTOR], Move* bestMoveToSave) {
    numNodes++;
    if (position->score <= -MATE_LOWER) {
        return -MATE_UPPER;
    }
    if (depth == 0) {
        return position->score;
    }

    int numMoves = genMoves(position, moves);
    if(doPatCheck && isPat(position, numMoves, moves) == true) {
        return 0;
    }

    if(canNullMove && depth > 3 && abs(position->score) < 500){
        Position target;
        char targetBoard[SIZE];
        Position* duplicatePos = duplicatePosition(position, &target, targetBoard);
        rotate(duplicatePos, true);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move bestChildMove;
        int score = -negamax(duplicatePos, depth - 3, -beta, -alpha, false, false, opponentMoves, &bestChildMove);
        if(score >= beta){
            return beta;
        }
    }

    currentBoard = position->board;
    qsort(moves, numMoves, sizeof(Move), compareMoves);

    int max = -INT_MAX;
    for (int i = 0; i < numMoves; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = &moves[i];
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move bestChildMove;

        int score = -negamax(newPosition, depth - 1, -beta, -alpha, true, true, opponentMoves, &bestChildMove);
        if (score >= MATE_LOWER) {
            score--; // winning mate found, add one point penalty per depth
        } else if (score <= -MATE_LOWER) {
            score++; // losing mate found, add one point penalty per depth
        }

        if (score > max) {
            max = score;
            *bestMoveToSave = *move;
        }
        alpha = (alpha > score) ? alpha : score;
        if (alpha >= beta) {
            break; // Beta cutoff
        }
    }
    return max;
}

void searchBestMove(Position* position, Move* bestMove, int timeLeftMs) {
    double timeTakenMs = 0.0;
    clock_t start = clock();
    for(int depth = 1; depth < maxDepth || (timeTakenMs < 150.0 && timeLeftMs > 10000); depth++){
        Move moves[MAX_BRANCHING_FACTOR];
        numNodes = 0;
        int score = negamax(position, depth, -INT_MAX, INT_MAX, false, false, moves, bestMove);
        timeTakenMs = clock() - start;
        printf("info depth %d score cp %d time %.2f nps %.2f\n", depth, score, timeTakenMs, timeTakenMs == 0.0 ? 0 : numNodes/(timeTakenMs/1000.0));
        fflush(stdout);
    }
}