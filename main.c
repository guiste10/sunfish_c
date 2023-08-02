#include <stdio.h>
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "uci.h"

int main() {
    initPst();
    initializePieceIndexArray();

    //char uciPosition[] = "position startpos moves e2e4 d7d5"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 g8h6 c1h6"; // mate in 2 (king eaten 4 plies)
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1"; // mate not found at depth 6???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6"; // mate not found at depth 5???
    //char uciPosition[] = "position startpos moves d2d4 e7e6 c2c4 f8b4 c1d2 b4d2 b1d2 b8c6 e2e3 g8e7 g1f3 a7a6 f1d3 e8g8 h2h4 d7d5 f3g5 h7h6 c4c5 h6g5 h4g5 g7g6 d1g4 c6b4 d3b1 b4c6 g4h4"; // ok mate found at depth 4
    //findBestMoveFromUciPosition(uciPosition);
    //findBestMoveTimeStamped((char*)randomBoard);
    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
