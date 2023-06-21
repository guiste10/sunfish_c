#include <stdio.h>
#include "pieceSquareTables.h"
#include "uci.h"
#include "debug.h"
#include "chessBoard.h"

int main() {
    initPst();
    //playUci();
    findBestMoveTimeStamped((char*)initialBoard);

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
