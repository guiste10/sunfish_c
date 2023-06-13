cmake_minimum_required(VERSION 3.25)
project(sunfish_c C)

set(CMAKE_C_STANDARD 23)

add_executable(sunfish_c main.c pieceSquareTables.h pieceSquareTables.c debug.c debug.h chessBoard.c chessBoard.h constants.c constants.h position.c position.h move.c move.h arraylist.c arraylist.h search.c search.h uci.c uci.h)
