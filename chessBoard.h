//
// Created by neiringu on 21-05-23.
//

#ifndef SUNFISH_C_CHESSBOARD_H
#define SUNFISH_C_CHESSBOARD_H

extern char PIECES[];
extern char PROMOTIONS[];
extern int NUM_PROMOTIONS;
extern char board[];

extern const int N;
extern const int E;
extern const int S;
extern const int W;

extern const int A1;
extern const int H1;
extern const int A8;
extern const int H8;

Map* createPieceDirections();

#endif //SUNFISH_C_CHESSBOARD_H
