#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"

const int maxDepth = 4; // minimal 4 else can produce illegal moves when in check
int numNodes = 0;

bool onlyKingMoves(ArrayList *moves, const char *string);

bool isPat(Position *position, ArrayList *moves);

bool isKingInCheck(Position *position);

bool allKingMovesLeadToDeath(Position *position, ArrayList *moves);

void freeMoves(Move **bestMoveToSave, ArrayList *moves) {
    for (int i = 0; i < moves->size; i++) {
        Move* move = arrayListGet(moves, i);
        if(move != *bestMoveToSave){
            free(move);
        }
    }
    freeArrayList(moves);
}

int negamax(Position* position, int depth, int alpha, int beta, bool doPatCheck, Move** bestMoveToSave) {
    numNodes++;
    if (position->score <= -MATE_LOWER) {
        return -MATE_UPPER;
    }
    if (depth == 0) {
        return position->score;
    }

    int max = -INT_MAX;
    ArrayList* moves = genMoves(position);

    if(doPatCheck && isPat(position, moves) == true) {
        return 0;
    };

    for (int i = 0; i < moves->size; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = arrayListGet(moves, i);
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move* bestChildMove = NULL;

        int score = -negamax(newPosition, depth - 1, -beta, -alpha, true, &bestChildMove);
        free(bestChildMove);
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
    freeMoves(bestMoveToSave, moves);
    return max;
}

bool isPat(Position *position, ArrayList *moves) {
    if(onlyKingMoves(moves, position->board)) {
        if(!isKingInCheck(position)){
            return allKingMovesLeadToDeath(position, moves);
        }
    }
    return false;
}

bool onlyKingMoves(ArrayList *moves, const char *board) {
    for (int i=0; i<moves->size; i++){
        Move* move = arrayListGet(moves, i);
        if(*(board + move->i) != 'K'){
            return false;
        }
    }
    return true;
}

bool isKingInCheck(Position *position) {
    Position* duplicatePos = duplicatePosition(position);
    rotate(duplicatePos, false);
    Move* bestChildMove = NULL;
    int score = negamax(duplicatePos, 1, -INT_MAX, INT_MAX, false, &bestChildMove);
    free(duplicatePos);
    free(bestChildMove);
    return score >= MATE_LOWER;
}

bool allKingMovesLeadToDeath(Position *position, ArrayList *moves) {
    for (int i=0; i < moves->size; i++){
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = arrayListGet(moves, i);
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move* bestChildMove = NULL;
        int score = negamax(newPosition, 1, -INT_MAX, INT_MAX, false, &bestChildMove);
        free(bestChildMove);
        if (score < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}

Move* searchBestMove(Position* position) {
    Move* bestMove = NULL;
    int score = negamax(position, maxDepth, -INT_MAX, INT_MAX, false, &bestMove);
    printf("info depth %d score cp %d\n", maxDepth, score);
    fflush(stdout);
    //printf("Score: %d\n", score);
    //printMove(*bestMove, position->board);
    return bestMove;
}