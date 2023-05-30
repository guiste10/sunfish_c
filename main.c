#include <stdio.h>
#include <malloc.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "position.h"
#include "move.h"

int main() {
    initPst();

    Position* position = initPosition();
    ArrayList* moves = genMoves(position);

    for(int i=0; i<20; i++){
        Move* move = arrayListGet(moves, i);
        printMove(*move, (char*)initialBoard);
        if(i == 0){
            char newBoard[SIZE];
            //printCharArray(position->board, SIZE);
            doMove(position, move, newBoard);
            printCharArray(newBoard, SIZE);
        }
        free(move);
    }



    freeArrayList(moves);

    // Free memory
    free(position);
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}