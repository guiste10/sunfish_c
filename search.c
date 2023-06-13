#include <limits.h>
#include <malloc.h>
#include "position.h"
#include "constants.h"

const int maxDepth = 1;
//const int maxDepth = 5;

int minimax(Position* position, int depth, Move** bestMoveToSave, int alpha, int beta) {
    int max = -INT_MAX;
    ArrayList* moves = genMoves(position);
    for (int i=0; i<moves->size; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = arrayListGet(moves, i);
        doMove(position, move, newPosition, newBoard);
        int score = newPosition->score;
        if(depth > 1){
            rotate(newPosition, false);
            Move* bestChildMove = NULL;
            score = -minimax(newPosition, depth - 1, &bestChildMove, -beta, -alpha);
            free(bestChildMove);
//            alpha = alpha > score ? alpha : score;
//            if(alpha >= beta){
//                break;
//            }
        }
        if( score > max ){
            if(*bestMoveToSave != NULL){
                free(*bestMoveToSave);
            }
            max = score;
            *bestMoveToSave = move;
        } else {
            free(move);
        }
    }
//    printf("Depth: %d, score: %d\n", depth, *max);
//    fflush(stdout);  // Flush the output stream
    freeArrayList(moves);
    return max;
}

Move* searchBestMove(Position* position) {
    Move* bestMove = NULL;
    int score = minimax(position, maxDepth, &bestMove, -INT_MAX, INT_MAX);
    printf("info depth %d score cp %d\n", maxDepth, score);
    fflush(stdout);
    //printf("Score: %d\n", score);
    //printMove(*bestMove, position->board);
    return bestMove;
}