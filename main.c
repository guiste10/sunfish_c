#include <stdio.h>
#include "debug.h"
#include "uci.h"

int main() {
    //char uciPosition[] = "position startpos moves"; // start pos
    //char uciPosition[] = "position startpos moves d2d4 d7d5 c2c4 d5c4 e2e3";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 g1f3 b8c6 g2g3 d7d5 f1g2 d8d6 c1f4 d6b4 d1d2 b4b2 e1g1 b2a1 c2c3 g7g5 f4g5 f6e4 d2c2 c8f5 f3d2 e4g3 e2e4 g3f1 g1f1 f5e4 g2e4 c6d4 c3d4 a1d4 g5e3 d4f6 e4d5 e8c8 c2b3 f6a6 d5c4 a6c6 f1e2 f7f6 e3a7 d8d6 a7e3 f8g7 b1c3 c6g2 b3a4";
    //char uciPosition[] = "position startpos moves d2d4 g8f6 c2c4 b8c6 g1f3 e7e6 e2e3 d7d5 b1c3 f8b4 a2a3 b4e7 c1d2 f6e4 c3e4 d5e4 f3g1 e8g8 d1c2 f7f5 g2g3 c8d7 f1g2 h7h5 g1e2 h5h4 e2f4 e7d6 e1c1 g7g5 f4h3 g5g4 h3f4 h4h3 g2f1 d6f4 g3f4 d8h4 d2b4 c6b4 a3b4 f8e8 h1g1 a8d8 g1g3 g8h8 c2c3 h8g8 f1h3 a7a6 d1g1 d7a4 h3g4 g8f7 g4e2 h4h2 d4d5"; // mate undetected by null move when plays e7d5 depth 7

    //char uciPosition[] = "position startpos moves g1f3 g8f6 g2g3 b8c6 d2d4 d7d5 b1c3 c8f5 f3h4 f5g6 h4g6 h7g6 c1f4 e7e6 c3b5 f8d6 b5d6 c7d6 f1g2 d8b6 f4d6 b6d4 d1d4 c6d4 a1c1 e8d7 d6c5 d4c6";



    char uciPosition[] = "position startpos moves e2e3 g7g6 d2d4 f8g7 h2h4 g8f6 g2g4 b8c6 g4g5 f6e4 f1g2 d7d5 g1e2 c8f5 b2b3 c6b4 c1a3 e4f2 e1f2 b4c2 a3b2 c2a1 b2a1 f5e4 g2e4 d5e4 d1c2 f7f5 g5f6 e8g8 c2e4 f8f6 e2f4 c7c5 d4c5 f6f4 e3f4 g7a1 e4b7 a1d4 f2e2 d4c5 b7e4 d8c8 h1c1 c8g4 e2d2 a8d8 d2c2"; // sac knight c5e3???
    findBestMoveFromUciPosition(uciPosition);

    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
