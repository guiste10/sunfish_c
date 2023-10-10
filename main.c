#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 c7c6 d4d5 e7e5 d5e6 d7e6 g1f3 d8d1 e1d1 f8c5 e2e4 g8f6 e4e5 f6e4 f1d3 e4f2 d1e2 f2h1 g2g4 h1f2 g4g5 f2d3 e2d3 e8g8 g5g6 f7g6 f3g5 h7h6 h2h4 h6g5 c1f4 g5f4 b1d2 f8d8 d3c3 c5d4 c3d3 d4b2 d3e2 b2a1 d2f1 a1e5 f1g3 f4g3 h4h5 g6h5 e2e3 d8f8 e3e4 g3g2 e4e3 g2g1q e3e2 f8f2 e2d3 f2h2 d3c4 h2c2 c4b3 c2e2 b3a3 a7a5 a3b3 a5a4 b3a3 b8d7 a3b4 e2a2 b4c4 g1e1 c4d3 a4a3 d3c4 a2b2 c4d3 b2h2 d3c4 a3a2 c4b3 a2a1q b3c4 a1b2 c4d3";


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
