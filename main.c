#include <stdio.h>
#include "debug.h"
#include "uci.h"

int main() {
    //char debug[] = "position startpos moves d2d4 g7g6 c2c4 f8g7 g1f3 g8f6 c1f4 d7d5 e2e3 e8g8 f1d3 f6h5 f4g3"; // duplicate queen appears bug
    //char debug[] = "position startpos moves e2e4 g7g6 d2d4 f8g7 e4e5 d7d6 f2f4 d6e5 f4e5 b8c6 g1f3 c8f5 c2c3 e7e6 f1d3 f5d3 d1d3 g7e5 f3e5 c6e5 d4e5 d8d3 b1d2"; // queen sac d3d2?
    //char debug[] = "position startpos moves g1f3 g7g6 g2g3 f8g7 b1c3 g8f6 e2e4 d7d6 d2d4 e8g8 c1g5 c8g4 f1e2 b8d7 e4e5 d6e5 d4e5 g4f3 e2f3 d7e5 f3g2 d8d1 a1d1 c7c6 e1f1 a8d8 d1e1 e5c4 e1e7 c4b2 e7b7 b2c4 b7a7 c4d2 f1g1 f8e8 g2c6 e8e1 g1g2 e1h1"; // should take rook with g2h1
    char debug[] = "position startpos moves e2e4 g7g6 f2f4 f8g7 d2d4 e7e5 d4e5 d8h4 g2g3"; // h4h2 sac queen???
    findBestMoveFromUciPosition(debug);

    //playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
