#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 g1f3 b8c6 g2g3 d7d5 f1g2 d8d6 c1f4 d6b4 d1d2 b4b2 e1g1 b2a1 c2c3 g7g5 f4g5 f6e4 d2c2 c8f5 f3d2 e4g3 e2e4 g3f1 g1f1 f5e4 g2e4 c6d4 c3d4 a1d4 g5e3 d4f6 e4d5 e8c8 c2b3 f6a6 d5c4 a6c6 f1e2 f7f6 e3a7 d8d6 a7e3 f8g7 b1c3 c6g2 b3a4";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 c2c4 b8c6 g1f3 e7e6 e2e3 d7d5 b1c3 f8b4 a2a3 b4e7 c1d2 f6e4 c3e4 d5e4 f3g1 e8g8 d1c2 f7f5 g2g3 c8d7 f1g2 h7h5 g1e2 h5h4 e2f4 e7d6 e1c1 g7g5 f4h3 g5g4 h3f4 h4h3 g2f1 d6f4 g3f4 d8h4 d2b4 c6b4 a3b4 f8e8 h1g1 a8d8 g1g3 g8h8 c2c3 h8g8 f1h3 a7a6 d1g1 d7a4 h3g4 g8f7 g4e2 h4h2 d4d5"; // mate undetected by null move when plays e7d5 depth 7

    char uciPosition[] = "position startpos moves e2e3 g7g6 d1f3 f8g7 d2d4 g8f6 e3e4 b8c6 c2c3 d7d5 e4d5 f6d5 f1c4 d5f6 c4b5 c8g4 b5c6 e8f8 f3g3 b7c6 c1f4 a8c8 f4e3 c8b8 b2b3 d8d6 e3f4 e7e5 f4e5 d6e6 e1f1 b8e8 f2f3 g4f5 h2h3 f6d5 b1a3 d5e3 f1f2 g7e5 d4e5 e6e5 g3e5 e8e5 g2g4 f5e6 b3b4 f8g7 f3f4 e5e4 a1e1 e6d5 h1h2 h8e8 g1f3 e4f4 e1e3 e8e3 f2e3 f4f3 e3d4 d5e6 a3b1 f3f4 d4e3 f4f1 b1a3 f1d1 c3c4 d1e1 e3d4 e1d1 d4e3 d1e1 e3d4";// pv e1d1 allows threefold repetition

    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
