#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include "position.h"
#include "constants.h"

const int maxDepth = 6;
int numNodes = 0;

void freeMoves(Move **bestMoveToSave, ArrayList *moves) {
    for (int i = 0; i < moves->size; i++) {
        Move* move = arrayListGet(moves, i);
        if(move != *bestMoveToSave){
            free(move);
        }
    }
    freeArrayList(moves);
}

int negamax(Position* position, int depth, int alpha, int beta, Move** bestMoveToSave) {
    numNodes++;
    if (depth == 0) {
        return position->score;
    }

    int max = -INT_MAX;
    ArrayList* moves = genMoves(position);

    for (int i = 0; i < moves->size; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = arrayListGet(moves, i);
        doMove(position, move, newPosition, newBoard);
        rotate(newPosition, false);
        Move* bestChildMove = NULL;

        int score = -negamax(newPosition, depth - 1, -beta, -alpha, &bestChildMove);
        free(bestChildMove);

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

Move* searchBestMove(Position* position) {
    Move* bestMove = NULL;
    int score = negamax(position, maxDepth, -INT_MAX, INT_MAX, &bestMove);
    printf("info depth %d score cp %d\n", maxDepth, score);
    fflush(stdout);
    //printf("Score: %d\n", score);
    //printMove(*bestMove, position->board);
    return bestMove;
}