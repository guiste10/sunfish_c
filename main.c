#include <stdio.h>
#include "debug.h"
#include "uci.h"

int main() {
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 g1f3 b8c6 g2g3 d7d5 f1g2 d8d6 c1f4 d6b4 d1d2 b4b2 e1g1 b2a1 c2c3 g7g5 f4g5 f6e4 d2c2 c8f5 f3d2 e4g3 e2e4 g3f1 g1f1 f5e4 g2e4 c6d4 c3d4 a1d4 g5e3 d4f6 e4d5 e8c8 c2b3 f6a6 d5c4 a6c6 f1e2 f7f6 e3a7 d8d6 a7e3 f8g7 b1c3 c6g2 b3a4";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 c2c4 b8c6 g1f3 e7e6 e2e3 d7d5 b1c3 f8b4 a2a3 b4e7 c1d2 f6e4 c3e4 d5e4 f3g1 e8g8 d1c2 f7f5 g2g3 c8d7 f1g2 h7h5 g1e2 h5h4 e2f4 e7d6 e1c1 g7g5 f4h3 g5g4 h3f4 h4h3 g2f1 d6f4 g3f4 d8h4 d2b4 c6b4 a3b4 f8e8 h1g1 a8d8 g1g3 g8h8 c2c3 h8g8 f1h3 a7a6 d1g1 d7a4 h3g4 g8f7 g4e2 h4h2 d4d5"; // mate undetected by null move when plays e7d5 depth 7

    char uciPosition[] = "position startpos moves g1f3 d7d6 g2g3 c7c6 b1c3 b7b5 f1g2 d8b6 d2d3 g7g6 c1e3 b6b7 e1g1 b5b4 c3e4 c8g4 h2h3 g4f3 g2f3 b7d7 f3g2 f8g7 c2c3 f7f5 e4g5 h7h6 g5f3 b4c3 b2c3 g7c3 f3h4 c3a1 d1a1 h8h7 h4g6 g8f6 a1c1 h6h5 c1c4 h7g7 g6f4 e7e5 c4e6 d7e7 e6c8 e8f7 f4e6 g7g8 e6g5 f7g6 c8e6 e7e6 g5e6 g8c8 f2f4 f6d7 f4e5 d6e5 d3d4 g6f6 d4d5 d7b6 e3g5 f6g6 e2e4 c6d5 e4f5 g6h7 f5f6 b8d7 f6f7 d7f8 e6f8 c8f8 g5e7 h7g6 e7f8 a8f8 f1e1 e5e4 a2a3 f8f7 e1c1 g6h7 g3g4 h5g4 h3g4 h7h6 g1h2 h6g5 h2h3 f7b7 c1c5 g5f4 h3h2 f4g4 g2h3 g4f4 a3a4 f4e5 a4a5 b6c4 a5a6 b7b6 c5c8 b6a6 h2g3 a6a3 g3g4 e5d4 c8e8 a7a5 g4h4 c4e5 e8g8 a3b3 h3e6 b3b6 g8e8 e4e3 e6g4 b6b2 g4h5 e3e2 h5e2 b2e2 e8a8 e2a2 h4g3 a2a3 g3f4 e5c6 a8e8 a3b3 e8a8 d4c5 a8e8 b3b1 e8a8 c5b5 f4f5 b5a4 f5f4 a4a3 a8a6 b1c1 a6a8 a3b4 a8c8 b4b5 f4e3 c1a1 c8a8 a1a2 a8e8 a2a3 e3f4 b5c4 e8c8 c4c5 f4f5 a3e3 f5f4 e3e7 f4f3 e7g7 f3e3 c5d6";
    findBestMoveFromUciPosition(uciPosition);

    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
