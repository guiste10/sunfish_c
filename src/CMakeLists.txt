cmake_minimum_required(VERSION 3.25)
project(sunfish_c C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O1")

add_executable(sunfish_c main.c pieceSquareTables.h pieceSquareTables.c chessBoard.c chessBoard.h constants.c constants.h position.c position.h move.c move.h search.c search.h uci.c uci.h zobrist.c zobrist.h randomUnsigned64bitIntegers.c randomUnsigned64bitIntegers.h tpMove.c tpMove.h tpScore.h tpScore.c moveScoreGenerator.c moveScoreGenerator.h perft.c perft.h)
