#include <stdio.h>
#include "debug.h"
#include "uci.h"

int main() {
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 g1f3 b8c6 g2g3 d7d5 f1g2 d8d6 c1f4 d6b4 d1d2 b4b2 e1g1 b2a1 c2c3 g7g5 f4g5 f6e4 d2c2 c8f5 f3d2 e4g3 e2e4 g3f1 g1f1 f5e4 g2e4 c6d4 c3d4 a1d4 g5e3 d4f6 e4d5 e8c8 c2b3 f6a6 d5c4 a6c6 f1e2 f7f6 e3a7 d8d6 a7e3 f8g7 b1c3 c6g2 b3a4";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 c2c4 b8c6 g1f3 e7e6 e2e3 d7d5 b1c3 f8b4 a2a3 b4e7 c1d2 f6e4 c3e4 d5e4 f3g1 e8g8 d1c2 f7f5 g2g3 c8d7 f1g2 h7h5 g1e2 h5h4 e2f4 e7d6 e1c1 g7g5 f4h3 g5g4 h3f4 h4h3 g2f1 d6f4 g3f4 d8h4 d2b4 c6b4 a3b4 f8e8 h1g1 a8d8 g1g3 g8h8 c2c3 h8g8 f1h3 a7a6 d1g1 d7a4 h3g4 g8f7 g4e2 h4h2 d4d5"; // mate undetected by null move when plays e7d5 depth 7

    //char uciPosition[] = "position startpos moves g1f3 b8c6 g2g3 g7g6 b1c3 f8g7 d2d4 d7d6 f1g2 g8f6 c1f4 e8g8 e2e3 f6h5 f4g5 h7h6 g5h4 g6g5 f3d2 g5h4 d1h5 h4g3 h2g3 e7e5 d2b3 e5d4 e3d4 f8e8 e1f1 c6d4 b3d4 g7d4 h5h6 d8f6 h6f6 d4f6 c3d5 f6d8 a2a4 c7c6 d5f4 c8f5 c2c4 d8f6 a1a3 f6b2 a3b3 b2e5 b3b7 e5f4 g2c6 f5d3 f1g2 d3e4 c6e4 e8e4 h1h4 e4c4 h4f4 c4f4 g3f4 g8g7 b7d7 g7f6 d7d6 f6f5 d6d7 f7f6 g2f3 a7a5 d7d5 f5e6 f3e4 f6f5 d5f5 a8b8 f5a5 b8b4 e4f3 b4b3 f3g4 e6f6 a5a6 f6g7 f4f5 b3b4 g4g5 g7f7 f2f4 b4b1 f5f6 b1g1 g5f5 g1f1 a6a7 f7f8 a4a5 f1a1 a5a6 a1a5 f5g6 f8e8 f6f7 e8f8 a7a8 f8e7 f7f8q e7e6";
    //findBestMoveFromUciPosition(uciPosition);

    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
