#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();

    //findBestMoveTimeStamped((char*)randomBoard);
    // ok char uciPosition[] = "position startpos moves e2e4 e7e5 f1c4 b8c6 d1f3 d8h4 f3f7"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves g2g3 e7e5 f1g2 g8f6 b2b3 f8c5 c1b2 d7d6 b1c3 e8g8 e2e3 c8g4 g1e2 c7c6 h2h3 g4f5 e1g1 c5b4 a2a3 b4a5 b3b4 a5c7 d2d3 f8e8 b4b5 f5g6 a3a4 b8d7 b5c6 d7c5 c6b7 a8b8 c3b5 a7a6 b5c7 d8c7 d3d4 c7b6 a1b1 c5a4 b2a1 b6c7 c2c4 a4b6 d4e5 g6b1 d1b1 d6e5 b1c2 c7c4 c2c4 b6c4 f1c1 c4e3 f2e3 h7h6 e2c3 f6h5 c3e4 b8b7 e4d6 b7e7 d6e8 e7e8 g1f2 f7f5 g2f3 h5f6 c1c6 e5e4 f3e2 f6d7 c6a6 d7c5 a6a7 g7g6 e2c4 c5e6 a7g7 g8f8 g7g6 f5f4 g3f4 e8a8 a1f6 a8e8 g6h6 f8f7 f6e5 e8d8 c4e6 f7e7 e5f6 e7e6 f6d8 e6f7 h6f6 f7g7 f6f5 g7g6 f5g5 g6h7 f4f5 h7h6 f5f6 h6g5 f6f7 g5g6 f7f8q g6h7 f8f6 h7g8 f2g3 g8h7 g3f4 h7g8 f4e4 g8h7 e4f5"; // illegal, king will die immediately because of queen
    //findBestMoveFromUciPosition(uciPosition);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
