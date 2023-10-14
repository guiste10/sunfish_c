#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 c7c6 d4d5 e7e5 d5e6 d7e6 g1f3 d8d1 e1d1 f8c5 e2e4 g8f6 e4e5 f6e4 f1d3";
    char uciPosition[] = "position startpos moves d2d4 e7e6 e2e3 d8f6 g1f3 h7h6 f1d3 b8c6 e1g1 c6b4 c2c4 d7d5 a2a3 b4d3 d1d3 b7b6 b2b4 a7a5 b4b5 c7c6 b5c6 c8a6 b1d2 f8d6 d3b3 f6d8 a3a4 g8e7 c1a3 d6a3 a1a3 e7c6 f1b1 c6b4 c4d5 d8d5 b3d5 e6d5 a3c3 a8c8 b1c1 e8g8 c3c8 f8c8 c1c8 a6c8 f3e5 b4c2 d2b1 f7f6 e5d3 g7g5 b1c3 c8b7 f2f4 c2e3 f4g5 h6g5 g1f2 e3c2 c3b5 b7c6 b5c7 c2d4 f2e3 d4c2 e3d2 c2d4 h2h4 g5h4 d3f4 d4b3 d2c3 b3c5 c7d5 c5a4 c3c2 g8f7 d5e3 c6e4 c2b3 b6b5 f4e2 f7g8 e2c3 a4c3 b3c3 e4g2 e3g2 h4h3 g2f4 h3h2 f4d5 h2h1q d5f6 g8h8 f6e4 h1e4 c3b3 e4b4 b3a2 b4c3 a2b1 h8g8 b1a2 b5b4 a2b1 a5a4 b1a2 c3e3 a2b1 e3f2 b1a1 f2g2 a1b1 g8h8 b1a1 g2f2 a1b1 h8g8 b1c1 b4b3 c1b1 f2c2 b1a1 c2f2 a1b1 f2c2 b1a1";

    //char uciPosition[] = "position startpos moves e2e4 d7d5"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 g8h6 c1h6"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1"; // mate not found at depth 6???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6"; // mate not found at depth 5???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6 g4h4"; // ok mate found at depth 4
    findBestMoveFromUciPosition(uciPosition);
    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
