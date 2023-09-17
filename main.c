#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    //char uciPosition[] = "position startpos moves"; // start pos
    char uciPosition[] = "e2e4 e7e6 d2d4 b8c6 g1f3 h7h6 f1d3 c6b4 e1g1 d7d5 b1c3 c8d7 c1f4 c7c6 a2a3 b4d3 d1d3 g7g5 f4g3 f7f5 e4f5 e6f5 g3e5 h8h7 f1e1 e8f7 g2g4 g8f6 g4f5 f7g8 e5f6 d8f6 f3e5 d7f5 d3g3 f5c2 e1e2 f6f5 a1e1 a8d8 e2e3 f8d6 e3f3 f5e6 g3g4 h7e7 g4e6 e7e6 f3e3 a7a6 c3a4 c2a4 b2b4 d8f8 e5d7 e6e3 e1e3 f8d8 d7f6 g8f8 b4b5 a6b5 e3f3 f8g7 f6g4 a4d1 g1g2 d1f3 g2f3 c6c5 f3g2"; // capture own piece??? nok

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
