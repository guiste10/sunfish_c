#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();

    //findBestMoveTimeStamped((char*)debugBoard);
    //char uciPosition[]  = "position startpos moves e2e4 e7e5 f1c4 b8c6 d1f3 d8h4 f3f7";
    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
