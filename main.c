#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves e2e4 e7e6 d2d4 b8c6 f1d3 e6e5 d4d5 c6b4 g1f3 b4d3 d1d3 f8d6 e1g1 f7f6 c2c4 g8e7 c1e3 e7g6 c4c5 d6e7 b1c3 d7d6 b2b4 d6c5 d3c4 c5b4 c3b5 c7c6 d5c6 c8g4 a1d1 d8c8 b5a7 a8a7 e3a7 b7c6 a7c5 c8b7 f3h4 e7c5 c4c5 g6h4 d1d6 e8e7 f1d1 g4d1 d6d1 e7e8 d1d6 e8e7 d6c6 e7d8 c5d6 b7d7 d6d7 d8d7 c6a6 h8c8 h2h3 c8c2 a2a4 b4a3 a6b6 a3a2 b6b7 d7c6 b7g7 c2c1 g1h2"; // under promotion?
    //char uciPosition[] = "position startpos moves e2e4 e7e6 d2d4 b8c6 f1d3 e6e5 d4d5 c6b4 g1f3 b4d3 d1d3 f8d6 e1g1 f7f6 c2c4 g8e7 c1e3 e7g6 c4c5 d6e7 b1c3 d7d6 b2b4 d6c5 d3c4 c5b4 c3b5 c7c6 d5c6 c8g4 a1d1 d8c8 b5a7 a8a7 e3a7 b7c6 a7c5 c8b7 f3h4 e7c5 c4c5 g6h4 d1d6 e8e7 f1d1 g4d1 d6d1 e7e8 d1d6 e8e7 d6c6 e7d8 c5d6 b7d7 d6d7 d8d7 c6a6 h8c8 h2h3 c8c2 a2a4 b4a3 a6b6 a3a2 b6b7 d7c6 b7g7 c2c1 g1h2 a2a1b g7g6 h7g6 f2f4"; // capture own piece?

    //char uciPosition[] = "position startpos moves e2e4 d7d5"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 g8h6 c1h6"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1"; // mate not found at depth 6???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6"; // mate not found at depth 5???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6 g4h4"; // ok mate found at depth 4
    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
