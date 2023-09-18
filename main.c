#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    //char uciPosition[] = "position startpos moves"; // start pos
    char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 b1c3 g8f6 g1f3 e8g8 e2e3 d7d6 f1d3 c8d7 e1g1 d7c6 a2a3 b4c3 b2c3 b8d7 e3e4 f6e4 d3e4 c6e4 c1g5 e4f3 g5d8 f3d1 a1d1 a8d8 d4d5 e6d5 c4d5 f8e8 f1e1 e8e1 d1e1 d7b6 f2f3 b6d5 a3a4 d5c3 a4a5 c3d5 a5a6 b7a6 e1d1 c7c6 d1e1 h7h6 e1e2 d8b8 g1f2 d5f4 e2d2 d6d5 d2c2 c6c5 c2d2 b8b3 g2g3 b3b2 d2b2 f4d3 f2g2 d3b2 g2h3 c5c4 h3g2 c4c3 g2h3 c3c2 h3g2 c2c1q g2h3 b2c4 h3g2 d5d4 g2h3 c4e3 h3h4 c1c2 h2h3";


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
