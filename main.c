#include <stdio.h>
#include <stdint.h>
#include "map.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "constants.h"
#include "position.h"
#include "move.h"


int main() {
    Map* pst = createPst();
    //printIntArray(map_get(pst, "P"), SIZE);

    Map* directions = createPieceDirections();
    //printIntArray((int*)map_get(directions, "R"), 4);

    //printCharArray(board, SIZE);

    Position* position = initPosition();
    ArrayList* moves = gen_moves(position, directions);

    for(int i=0; i<20; i++){
        Move* move = arrayListGet(moves, i);
        printMove(*move, board);
    }
    //Move* move = arrayListGet(moves, 2);
    //printMove(*move, board);

    // Free memory
    map_destroy(pst);
    map_destroy(directions);
    printf("\n");
    fflush(stdout);  // Flush the output stream
    return 0;
}