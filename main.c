#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();

    //char uciPosition[] = "position startpos moves e2e4 d7d5"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 e7e6 g1f3 c7c5 d4c5 d8a5 b1c3 b8c6 c1d2 g8f6 e2e3 f8c5 f1c4 a5b4 c4b3 b4g4 e1g1 c6a5 f1e1 a7a6 h2h3 g4h5 d1e2 b7b5 e3e4 c8b7 g1h1 b5b4 c3a4 f6e4 a4c5 h5c5 d2e3 c5b5 e2b5 a6b5 e3d2 a5b3 a2b3 a8a1 e1a1 e4f2 h1g1 f2h3 g2h3 b7c6 g1f2 e8f8 d2f4 c6e4 a1a7 h7h6 f3d4 e6e5 f4e5 f7f6 e5d6";
    //findBestMoveFromUciPosition(uciPosition);
    //findBestMoveTimeStamped((char*)randomBoard);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
