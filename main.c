#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 g1f3 b8c6 g2g3 d7d5 f1g2 d8d6 c1f4 d6b4 d1d2 b4b2 e1g1 b2a1 c2c3 g7g5 f4g5 f6e4 d2c2 c8f5 f3d2 e4g3 e2e4 g3f1 g1f1 f5e4 g2e4 c6d4 c3d4 a1d4 g5e3 d4f6 e4d5 e8c8 c2b3 f6a6 d5c4 a6c6 f1e2 f7f6 e3a7 d8d6 a7e3 f8g7 b1c3 c6g2 b3a4";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 c2c4 b8c6 g1f3 e7e6 e2e3 d7d5 b1c3 f8b4 a2a3 b4e7 c1d2 f6e4 c3e4 d5e4 f3g1 e8g8 d1c2 f7f5 g2g3 c8d7 f1g2 h7h5 g1e2 h5h4 e2f4 e7d6 e1c1 g7g5 f4h3 g5g4 h3f4 h4h3 g2f1 d6f4 g3f4 d8h4 d2b4 c6b4 a3b4 f8e8 h1g1 a8d8 g1g3 g8h8 c2c3 h8g8 f1h3 a7a6 d1g1 d7a4 h3g4 g8f7 g4e2 h4h2 d4d5"; // mate undetected by null move when plays e7d5 depth 7

    char uciPosition[] = "position startpos moves e2e4 g7g6 d2d4 f8g7 g1f3 e7e6 c2c4 g8e7 b1c3 b8c6 c1e3 e8g8 f1e2 d7d6 e1g1 h7h6 d1d2 g6g5 h2h3 f7f5 e4f5 e7f5 d4d5 c6a5 d5e6 c8e6 b2b3 c7c6 a1d1 d8f6 c3e4 f6d8 e4d6 f5d6 d2d6 d8d6 d1d6 a8e8 f1d1 g5g4 h3g4 c6c5 e3c5 e6g4 g1f1 b7b6 c5e3 a5b7 d6d7 g4d7 d1d7 f8f7 d7f7 g8f7 f3d4 f7g6 e2d3 g6h5 d4f5 g7f6 f5h6 e8e3 f2e3 h5h6 d3e4 b7c5 e4d5 c5d3 f1e2 d3c1 e2f3 c1a2 g2g4 a2c1 b3b4 c1d3 b4b5 f6h4 f3e4 d3e1 e4f5 e1c2 e3e4 c2d4 f5e5 d4c2 e5d6 h4g3 d6c6 h6g5 c6b7 g5g4 b7a7 g3f2 a7a6 g4f4 a6b7 c2e3 b7c6 f4e5 c6b6"; // should do e3d5 with double check
    //char uciPosition[] = "position startpos moves e2e4 g7g6 d2d4 f8g7 g1f3 e7e6 c2c4 g8e7 b1c3 b8c6 c1e3 e8g8 f1e2 d7d6 e1g1 h7h6 d1d2 g6g5 h2h3 f7f5 e4f5 e7f5 d4d5 c6a5 d5e6 c8e6 b2b3 c7c6 a1d1 d8f6 c3e4 f6d8 e4d6 f5d6 d2d6 d8d6 d1d6 a8e8 f1d1 g5g4 h3g4 c6c5 e3c5 e6g4 g1f1 b7b6 c5e3 a5b7 d6d7 g4d7 d1d7 f8f7 d7f7 g8f7 f3d4 f7g6 e2d3 g6h5 d4f5 g7f6 f5h6 e8e3 f2e3 h5h6 d3e4 b7c5 e4d5 c5d3 f1e2 d3c1 e2f3 c1a2 g2g4 a2c1 b3b4 c1d3 b4b5 f6h4 f3e4 d3e1 e4f5 e1c2 e3e4 c2d4 f5e5 d4c2 e5d6 h4g3 d6c6 h6g5 c6b7 g5g4 b7a7 g3f2 a7a6 g4f4 a6b7 c2e3 b7c6 f4e5 c6b6 e5f6"; // should do e3d5 with double check

    findBestMoveFromUciPosition(uciPosition);
    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
