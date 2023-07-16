#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    playUci();
    //findBestMoveTimeStamped((char*)debugBoard);

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
