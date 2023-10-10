cmake_minimum_required(VERSION 3.25)
project(sunfish_c C)

set(CMAKE_C_STANDARD 23)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -g -O3") # for perf tool

add_executable(sunfish_c main.c pieceSquareTables.h pieceSquareTables.c debug.c debug.h chessBoard.c chessBoard.h constants.c constants.h position.c position.h move.c move.h search.c search.h uci.c uci.h utils.c utils.h zobrist.c zobrist.h randomUnsigned64bitIntegers.c randomUnsigned64bitIntegers.h transpositionTable.c transpositionTable.h)
