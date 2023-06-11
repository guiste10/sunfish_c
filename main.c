#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "position.h"
#include "move.h"
#include "search.h"


int main() {
    initPst();

    Position pos;
    Position* position = &pos;
    initPosition(position);
    Move* bestMove = searchBestMove(position);
    //printMove(*bestMove, position->board);
    printf("Best move search finished\n");

    Position newPosition;
    char newBoard[SIZE];
    doMove(position, bestMove, &newPosition, newBoard);
    free(bestMove);
    printCharArray(newBoard, SIZE);

//    ArrayList* moves = genMoves(position);
//    for(int i=0; i<20; i++){
//        Move* move = arrayListGet(moves, i);
//        printMove(*move, (char*)initialBoard);
//        if(i == 0){
//            Position newPosition;
//            char newBoard[SIZE];
//            doMove(position, move, &newPosition, newBoard);
//            printCharArray(newBoard, SIZE);
//        }
//        free(move);
//    }
//    freeArrayList(moves);

    // Free memory
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}