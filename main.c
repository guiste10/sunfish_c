#include <stdio.h>
#include <stdint.h>
#include "map.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "constants.h"


int main() {
    map* pst = createPst();
    //printIntArray(map_get(pst, "P"), SIZE);

    map* directions = createPieceDirections();
    //printIntArray((int*)map_get(directions, "R"), 4);

    printCharArray(board, SIZE);


    // Free memory
    map_destroy(pst);
    map_destroy(directions);
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}