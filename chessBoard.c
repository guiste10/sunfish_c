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

const int pawnDirections[] = {N, N+N, N+W, N+E};
const int knightDirections[] = {N+N+E, E+N+E, E+S+E, S+S+E, S+S+W, W+S+W, W+N+W, N+N+W};
const int bishopDirections[] = {N+E, S+E, S+W, N+W};
const int rookDirections[] = {N, E, S, W};
const int kingDirections[] = {N, E, S, W, N+E, S+E, S+W, N+W};

const char PIECES[] = "PNBRQK";

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

map* createPieceDirections(){
    map* directions = map_create();
    map_put(directions, "P", pawnDirections);
    map_put(directions, "N", knightDirections);
    map_put(directions, "B", bishopDirections);
    map_put(directions, "R", rookDirections);
    map_put(directions, "Q", kingDirections);
    map_put(directions, "K", kingDirections);
    return directions;
}
