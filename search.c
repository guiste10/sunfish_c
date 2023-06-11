#include <limits.h>
#include <malloc.h>
#include "position.h"
#include "constants.h"

const int maxDepth = 2;
//const int maxDepth = 5;

Move* minimax(Position* position, int depth, int* max) {
    Move* maxMove = NULL;
    ArrayList* moves = genMoves(position);
    for (int i=0; i<moves->size; i++) {
        Position newPos;
        Position* newPosition = &newPos;
        char newBoard[SIZE];
        Move* move = arrayListGet(moves, i);
        doMove(position, move, newPosition, newBoard);
        int score;
        if(depth == 1){
            score = - position->score;
        } else {
            minimax(newPosition, depth - 1, &score);
        }
        if( score > *max ){
            if(maxMove != NULL){
                free(maxMove);
            }
            *max = score;
            maxMove = move;
        } else {
            free(move);
        }
    }
    freeArrayList(moves);
    return maxMove;
}

Move* searchBestMove(Position* position) {
    int score = -INT_MAX;
    Move* bestMove = minimax(position, maxDepth, &score);
    printf("Score: %d\n", score);
    printMove(*bestMove, position->board);
    return bestMove;
}