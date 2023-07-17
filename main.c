#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();

    //findBestMoveTimeStamped((char*)debugBoard);
    //char uciPosition[]  = "position startpos moves e2e4 d7d5 e4d5 d8d5 b1c3 d5e6 g1e2 c7c6 g2g3 g8f6 f1g2 e8d8 e1g1 e6g4 d2d4 c8f5 d4d5 d8c8 c1f4 f6d5 c3d5 c6d5 d1d5 b8c6 e2d4 c6d4 d5b7";
    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
