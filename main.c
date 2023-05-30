#include <stdio.h>
#include <malloc.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "position.h"
#include "move.h"


int main() {
    initPst();
    //printIntArray(map_get(pst, "P"), SIZE);

    //printIntArray((int*)map_get(directions, "R"), 4);

    //printCharArray(board, SIZE);

    Position* position = initPosition();
    ArrayList* moves = genMoves(position);

    for(int i=0; i<20; i++){
        Move* move = arrayListGet(moves, i);
        printMove(*move, (char*)initialBoard);
        free(move);
    }
    freeArrayList(moves);
    //Move* move = arrayListGet(moves, 2);
    //printMove(*move, board);

    // Free memory
    free(position);
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}