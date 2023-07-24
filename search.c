#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"

const int maxDepth = 6;
int numNodes = 0;
char* currentBoard;

bool onlyKingMoves(Move moves[MAX_BRANCHING_FACTOR], int numMoves, const char *string);
bool isPat(Position *position, int numMoves, Move moves[MAX_BRANCHING_FACTOR]);
bool isKingInCheck(Position *position);
bool allKingMovesLeadToDeath(Position *position, int numMoves, Move kingMoves[MAX_BRANCHING_FACTOR]);
void sortMoves(Move moves[MAX_BRANCHING_FACTOR], Position* position);

int negamax(Position* position, int depth, int alpha, int beta, bool doPatCheck, Move moves[MAX_BRANCHING_FACTOR], Move** bestMoveToSave) {
    numNodes++;
    if (position->score <= -MATE_LOWER) {
        return -MATE_UPPER;
    }
    if (depth == 0) {
        return position->score;
    }


    int numMoves = genMoves(position, moves);

    int max = -INT_MAX;


    if(doPatCheck && isPat(position, numMoves, moves) == true) {
        return 0;
    };

    //sortMoves(moves, position);

    for (int i = 0; i < numMoves; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = &moves[i];
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move* bestChildMove = NULL;

        int score = -negamax(newPosition, depth - 1, -beta, -alpha, true, opponentMoves, &bestChildMove);
        if (score >= MATE_LOWER) {
            score--; // winning mate found, add one point penalty per depth
        } else if (score <= -MATE_LOWER) {
            score++; // losing mate found, add one point penalty per depth
        }

        if (score > max) {
            max = score;
            *bestMoveToSave = move;
        }
        alpha = (alpha > score) ? alpha : score;
        if (alpha >= beta) {
            break; // Beta cutoff
        }
    }
    return max;
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
    Move* bestChildMove = NULL;
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
        Move* bestChildMove = NULL;
        int score = negamax(newPosition, 1, -INT_MAX, INT_MAX, false, opponentMoves, &bestChildMove);
        if (score < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}

void searchBestMove(Position* position, Move** bestMove) {
    Move moves[MAX_BRANCHING_FACTOR];
    int score = negamax(position, maxDepth, -INT_MAX, INT_MAX, false, moves, bestMove);
    printf("info depth %d score cp %d\n", maxDepth, score);
    fflush(stdout);
    //printf("Score: %d\n", score);
    //printMove(*bestMoveStack, position->board);
}

//int compareMoves(const void* a, const void* b) {
//    Move* moveA = (Move*)a; // 0xc91780
//    Move* moveB = (Move*)b; // 0xc918ac
//    char pieceFromA = currentBoard[moveA->i]; //b930
//    char pieceToA = currentBoard[moveA->j];
//    char pieceFromB = currentBoard[moveB->i];
//    char pieceToB = currentBoard[moveB->j];
//
//    if(pieceToA == pieceToB){
//        return 0;
//    }
//    if(pieceToA != '.'){
//        return 1;
//    }
//    if(pieceToB != '.'){
//        return -1;
//    }
//    return 0;
//}
//
//void sortMoves(Move moves[MAX_BRANCHING_FACTOR], Position* position) {
//    currentBoard = position->board;
////    Move* moveA = arrayListGet(moves, 0);
////    Move* moveB = (Move*)*(moves->array);
////    size_t size = sizeof(Move); // 12
////    size_t size2 = sizeof(void*); // 12
////    Move* moveC = moves->array[0]; //0xc91780 // b410
////    Move* moveD = moves->array[1]; //0xc917c0 // b430
////    Move* moveE = moves->array[2]; //0xc917c0
////
////    Move* moveZ = moves->array[25];
////    qsort(*(moves->array), moves->size, 32, compareMoves);
//
////    Move moveArray[2];
////    moveArray[0] = *((Move*)moves->array[0]);
////    moveArray[1] = *((Move*)moves->array[1]);
////    qsort(moveArray, 2, sizeof(Move), compareMoves);
//}