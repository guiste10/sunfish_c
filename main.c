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

    //char uciPosition[] = "position startpos moves e2e3 g7g6 d2d4 f8g7 h2h4 g8f6 g2g4 e8g8 g4g5 f6e4 d1f3 d7d5 c2c4 c8f5 c4d5 d8d5 b1d2 d5a5 f1d3 e4f2 d3f5 f2h1 f5e4 b8c6 f3h1 e7e5 e4c6 b7c6 h1c6 e5d4 e3e4 a5e5 g1f3 e5g3 e1d1 f8e8 c6d5 a8d8 d5b5 d4d3 b5c5 e8e4 c5c6 e4e3 d2f1 g3f3 c6f3 e3f3 f1d2 f3f4 a1b1 f4h4 d2f3 h4h1 f3e1 d8e8 c1d2 g7e5 b1c1 e5g3 c1c3 g3e1 c3d3 e8e4 d3d7 e4d4 d7d4 e1f2 d1c2 f2d4 d2f4 d4b6 b2b4 h1f1 f4d2 f1f2 c2d1 g8g7 a2a4 f2f1 d1e2 f1f2 e2d1 f2f5 d1c2 f5f3 d2c3 g7g8 c3f6 h7h6 f6d8 f3f2 c2b3 f2f3 b3c2 h6g5 d8g5 f3f5 g5c1 f5f2 c2c3 f2f3 c3c4 f3f2 c4c3 f2f1 c1d2 f1f3 c3c4 f3f2 d2c3 f2f5 a4a5 b6e3 c4d3 e3f4 d3c4 f4d6 c3d2 d6f4 d2c3 f4e5 c3d2 f5f3 c4d5 e5d6 d5c4 g8h7 c4b5 f3a3 b5a6 a3a2 d2c3 a2c2 c3e1 c2e2 e1c3 e2c2 c3e1 c2e2 e1c3 e2e3 c3d2 e3d3 d2e1 d3d1 e1c3 d1d3 c3e1 d3d1 e1c3 d1d3 c3e1";

    //char uciPosition[] = "position startpos moves e2e3 g7g6 d2d4 f8g7 h2h4 g8f6 g2g4 e8g8 g4g5 f6e4 d1f3 d7d5 c2c4 c8f5 c4d5 d8d5 b1d2 d5a5 f1d3 e4f2 d3f5 f2h1 f5e4 b8c6 f3h1 e7e5 e4c6 b7c6 h1c6 e5d4 e3e4 a5e5 g1f3 e5g3 e1d1 f8e8 c6d5 a8d8 d5b5 d4d3 b5c5 e8e4 c5c6 e4e3 d2f1 g3f3 c6f3 e3f3 f1d2 f3f4 a1b1 f4h4 d2f3 h4h1 f3e1 d8e8 c1d2 g7e5 b1c1 e5g3 c1c3 g3e1 c3d3 e8e4 d3d7 e4d4 d7d4 e1f2 d1c2 f2d4 d2f4 d4b6 b2b4 h1f1 f4d2 f1f2 c2d1 g8g7 a2a4 f2f1 d1e2 f1f2 e2d1 f2f5 d1c2 f5f3 d2c3 g7g8 c3f6 h7h6 f6d8 f3f2 c2b3 f2f3 b3c2 h6g5 d8g5 f3f5 g5c1 f5f2 c2c3 f2f3 c3c4 f3f2 c4c3 f2f1 c1d2 f1f3 c3c4 f3f2 d2c3 f2f5 a4a5 b6e3 c4d3 e3f4 d3c4 f4d6 c3d2 d6f4 d2c3 f4e5 c3d2 f5f3 c4d5 e5d6 d5c4 g8h7 c4b5 f3a3 b5a6 a3a2 d2c3 a2c2 c3e1 c2e2 e1c3 e2c2 c3e1 c2e2 e1c3 e2e3 c3d2 e3d3 d2e1 d3d1 e1c3 d1d3 c3e1 d3d1 e1c3"; // pq d1d3 pour autoriser draw?
    char uciPosition[] = "position startpos moves e2e3 g7g6 d2d4 f8g7 h2h4 g8f6 g2g4 e8g8 g4g5 f6e4 d1f3 d7d5 c2c4 c8f5 c4d5 d8d5 b1d2 d5a5 f1d3 e4f2 d3f5 f2h1 f5e4 b8c6 f3h1 e7e5 e4c6 b7c6 h1c6 e5d4 e3e4 a5e5 g1f3 e5g3 e1d1 f8e8 c6d5 a8d8 d5b5 d4d3 b5c5 e8e4 c5c6 e4e3 d2f1 g3f3 c6f3 e3f3 f1d2 f3f4 a1b1 f4h4 d2f3 h4h1 f3e1 d8e8 c1d2 g7e5 b1c1 e5g3 c1c3 g3e1 c3d3 e8e4 d3d7 e4d4 d7d4 e1f2 d1c2 f2d4 d2f4 d4b6 b2b4 h1f1 f4d2 f1f2 c2d1 g8g7 a2a4 f2f1 d1e2 f1f2 e2d1 f2f5 d1c2 f5f3 d2c3 g7g8 c3f6 h7h6 f6d8 f3f2 c2b3 f2f3 b3c2 h6g5 d8g5 f3f5 g5c1 f5f2 c2c3 f2f3 c3c4 f3f2 c4c3 f2f1 c1d2 f1f3 c3c4 f3f2 d2c3 f2f5 a4a5 b6e3 c4d3 e3f4 d3c4 f4d6 c3d2 d6f4 d2c3 f4e5 c3d2 f5f3 c4d5 e5d6 d5c4 g8h7 c4b5 f3a3 b5a6 a3a2 d2c3 a2c2 c3e1 c2e2 e1c3 e2c2 c3e1 c2e2 e1c3 e2e3 c3d2 e3d3 d2e1 d3d1 e1c3 d1d3 c3e1 d3d1 e1c3 d1g1 c3d2 d6g3 d2c3 g3f2 b4b5 f2e3 c3b2 h7h6 b2c3"; // pq d1d3 pour autoriser draw?

    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
