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
    //printCharArray(newBoard, SIZE);

    // Free memory
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}