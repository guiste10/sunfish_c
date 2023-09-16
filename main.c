#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();
    char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3 d8d5 b1c3 d5c6 g1f3 b8d7 a2a4 g8f6 f3d2 e7e6 f1c4 c6g2 d1f3 g2f3 d2f3 f8b4 h1g1 e8g8 e3e4 f6e4 c1h6 e4c3 h6g7 c3d5 e1d1 f8e8 g7h6 g8h8 h6g7 h8g8 c4d3 f7f5 f3e5 d7e5 d4e5 d5f4 d1c2 f4h3 g1g3 h3f2 g7h6 g8h8 h6g7 h8g8 a1g1 c8d7 g7f6 f2g4 h2h3 b4c5 g1g2 d7a4 b2b3 a4c6 h3g4 f5f4 d3h7 g8h7 g3h3 h7g6 g2h2 f4f3 h3h6 g6f7 h6h7 f7f8 h7h8";

    // illegal rook move while in check using quiescence search
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3 d8d5 b1c3 d5c6 g1f3 b8d7 a2a4 g8f6 f3d2 e7e6 f1c4 c6g2 d1f3 g2f3 d2f3 f8b4 h1g1 e8g8 e3e4 f6e4 c1h6 e4c3 h6g7 c3d5 e1d1 f8e8 g7h6 g8h8 h6g7 h8g8 c4d3 f7f5 f3e5 d7e5 d4e5 d5f4 d1c2 f4h3 g1g3 h3f2 g7h6 g8h8 h6g7 h8g8 a1g1 c8d7 g7f6 f2g4 h2h3 b4c5 g1g2 d7a4 b2b3 a4c6 h3g4 f5f4 d3h7 g8h7 g3h3 h7g6 g2h2 f4f3 h3h6 g6f7 h6h7 f7f8 h7h8";
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3 d8d5 b1c3 d5c6 g1f3 b8d7 a2a4 g8f6 f3d2 e7e6 f1c4 c6g2 d1f3 g2f3 d2f3 f8b4 h1g1 e8g8 e3e4 f6e4 c1h6 e4c3 h6g7 c3d5 e1d1 f8e8 g7h6 g8h8 h6g7 h8g8 c4d3 f7f5 f3e5 d7e5 d4e5 d5f4 d1c2 f4h3 g1g3 h3f2 g7h6 g8h8 h6g7 h8g8 a1g1 c8d7 g7f6 f2g4 h2h3 b4c5 g1g2 d7a4 b2b3 a4c6 h3g4 f5f4 d3h7 g8h7 g3h3 h7g6 g2h2 f4f3 h3h6 g6f7 h6h7 f7f8 h7h8 f8f7 h2h7";


    //char uciPosition[] = "position startpos moves e2e4 d7d5"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 g8h6 c1h6"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1"; // mate not found at depth 6???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6"; // mate not found at depth 5???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6 g4h4"; // ok mate found at depth 4
    findBestMoveFromUciPosition(uciPosition);
    //findBestMoveTimeStamped((char*)initialBoard);
    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
