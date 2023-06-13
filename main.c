#include <stdio.h>
#include "pieceSquareTables.h"
#include "position.h"
#include "uci.h"

int main() {
    initPst();
    playUci();

//    Move* bestMove = searchBestMove(position);
//    printf("Best move search finished\n");
//    Position newPosition;
//    char newBoard[SIZE];
//    doMove(position, bestMove, &newPosition, newBoard);
//    printMove(*bestMove, position->board);
//    printCharArray(newBoard, SIZE);
//    free(bestMove);

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}