#include "map.h"

//
// Created by neiringu on 21-05-23.
//
const int A1 = 91;
const int H1 = 98;
const int A8 = 21;
const int H8 = 28;

const int N = -10;
const int E = 1;
const int S = 10;
const int W = -1;

const int pawnDirections[] = {N, N+N, N+W, N+E, 0};
const int knightDirections[] = {N+N+E, E+N+E, E+S+E, S+S+E, S+S+W, W+S+W, W+N+W, N+N+W, 0};
const int bishopDirections[] = {N+E, S+E, S+W, N+W, 0};
const int rookDirections[] = {N, E, S, W, 0};
const int kingDirections[] = {N, E, S, W, N+E, S+E, S+W, N+W, 0};

const char PIECES[] = "PNBRQK";
const char PROMOTIONS[] = "NBRQ";
const int NUM_PROMOTIONS = 4;

char board[] = "          "
                    "          "
                    " rnbqkbnr "
                    " pppppppp "
                    " ........ "
                    " ........ "
                    " ........ "
                    " ........ "
                    " PPPPPPPP "
                    " RNBQKBNR "
                    "          "
                    "          ";

Map* createPieceDirections(){
    Map* directions = map_create();
    map_put(directions, "P", (int*)pawnDirections);
    map_put(directions, "N", (int*)knightDirections);
    map_put(directions, "B", (int*)bishopDirections);
    map_put(directions, "R", (int*)rookDirections);
    map_put(directions, "Q", (int*)kingDirections);
    map_put(directions, "K", (int*)kingDirections);
    return directions;
}
