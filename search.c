#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"

const int maxDepth = 1;
int numNodes = 0;
char* currentBoard;

bool onlyKingMoves(Move moves[MAX_BRANCHING_FACTOR], int numMoves, const char *string);
bool isPat(Position *position, int numMoves, Move moves[MAX_BRANCHING_FACTOR]);
bool isKingInCheck(Position *position);
bool allKingMovesLeadToDeath(Position *position, int numMoves, Move kingMoves[MAX_BRANCHING_FACTOR]);

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

int negamax(Position* position, int depth, int alpha, int beta, bool doPatCheck, Move moves[MAX_BRANCHING_FACTOR], Move* bestMoveToSave) {
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

        int score = -negamax(newPosition, depth - 1, -beta, -alpha, true, opponentMoves, &bestChildMove);
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

void searchBestMove(Position* position, Move* bestMove) {
    Move moves[MAX_BRANCHING_FACTOR];
    int score = negamax(position, maxDepth, -INT_MAX, INT_MAX, false, moves, bestMove);
    printf("info depth %d score cp %d\n", maxDepth, score);
    fflush(stdout);
}

bool isPat(Position* position, int numMoves, Move moves[MAX_BRANCHING_FACTOR]) {
    if(onlyKingMoves(moves, numMoves, position->board)) {
        if(!isKingInCheck(position)){
            return allKingMovesLeadToDeath(position, numMoves, moves);
        }
    }
    return false;
}

bool onlyKingMoves(Move moves[MAX_BRANCHING_FACTOR], int numMoves, const char *board) {
    for (int i=0; i<numMoves; i++){
        if(*(board + moves[i].i) != 'K'){
            return false;
        }
    }
    return true;
}

bool isKingInCheck(Position *position) {
    Position* duplicatePos = duplicatePosition(position);
    rotate(duplicatePos, false);
    Move opponentMoves[MAX_BRANCHING_FACTOR];
    Move bestChildMove;
    int score = negamax(duplicatePos, 1, -INT_MAX, INT_MAX, false, opponentMoves, &bestChildMove);
    free(duplicatePos);
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
        int score = negamax(newPosition, 1, -INT_MAX, INT_MAX, false, opponentMoves, &bestChildMove);
        if (score < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}